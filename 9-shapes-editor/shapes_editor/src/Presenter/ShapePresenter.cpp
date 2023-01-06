#include "Presenter/ShapePresenter.h"

using namespace presenter;

ShapePresenter::ShapePresenter(model::IShapeComposition* shapeComposition, view::IView* view)
	: m_shapeComposition(shapeComposition)
	, m_view(view)
{
	m_shapeComposition->RegisterOnChange(this);
}

void ShapePresenter::OnChange(const std::vector<model::ShapePtr>& shapes)
{
	m_shapes = shapes;
	UpdateView();
}

void ShapePresenter::OnMouseDown()
{
	common::Point pos = m_view->GetMousePos();
	ChangeShapeSelection(pos.x, pos.y);

	if (m_selection.shape)
	{
		auto pressedResizeNode = GetPressedResizeNode(pos.x, pos.y);
		if (pressedResizeNode != ResizeNode::None)
		{
			m_resizeNode = pressedResizeNode;
		}
		else
		{
			m_isMoving = true;
		}
	}
}

void ShapePresenter::OnMouseUp()
{
	if (m_selection.shape &&
		(m_selection.topLeft != m_selection.shape->GetTopLeft() ||
		m_selection.bottomRight != m_selection.shape->GetBottomRight()))
	{
		m_selection.shape->Resize(m_selection.topLeft, m_selection.bottomRight);
		if (m_resizeNode != ResizeNode::None)
		{
			m_resizeNode = ResizeNode::None;
		}
		else if (m_isMoving)
		{
			m_isMoving = false;
		}
	}
}

void ShapePresenter::OnMouseDrag()
{
	if (m_selection.shape)
	{
		common::Point delta = m_view->GetMouseDelta();

		if (delta.x != 0.0f || delta.y != 0.0f)
		{
			if (m_resizeNode != ResizeNode::None)
			{
				OnShapeResize(delta.x, delta.y);
			}
			else if (m_isMoving)
			{
				OnShapeMove(delta.x, delta.y);
			}

			UpdateView();
		}
	}
}

void ShapePresenter::UpdateSelectedShapeData() const
{
	m_view->SetSelectedShapeData({
		m_selection.topLeft,
		m_selection.bottomRight,
		m_selection.shape->GetFillColor(),
		m_selection.shape->GetBorderColor()
	});
}

void ShapePresenter::ChangeShapeSelection(float x, float y)
{
	if (auto shape = m_shapeComposition->FindShapeAtCoords(x, y))
	{
		if (!m_selection.shape || m_selection.shape->GetId() != shape->GetId())
		{
			m_shapeComposition->LiftShapeOnTop(shape->GetId());
			m_selection.shape = shape;
			m_selection.topLeft = shape->GetTopLeft();
			m_selection.bottomRight = shape->GetBottomRight();
			UpdateView();
		}
	}
	else
	{
		m_selection.shape.reset();
		UpdateView();
	}
}

ResizeNode ShapePresenter::GetPressedResizeNode(float x, float y) const
{
	if (!m_selection.shape)
	{
		return ResizeNode::None;
	}

	auto tl = m_selection.shape->GetTopLeft();
	auto br = m_selection.shape->GetBottomRight();

	if (tl.y <= y && y <= tl.y + constants::ResizeMarkerSize) // maybe top left or top right
	{
		if (tl.x <= x && x <= tl.x + constants::ResizeMarkerSize)
		{
			return ResizeNode::TopLeft;
		}
		else if (br.x - constants::ResizeMarkerSize <= x && x <= br.x)
		{
			return ResizeNode::TopRight;
		}
	}
	else if (br.y - constants::ResizeMarkerSize <= y && y <= br.y) // maybe bottom left or bottom right
	{
		if (tl.x <= x && x <= tl.x + constants::ResizeMarkerSize)
		{
			return ResizeNode::BottomLeft;
		}
		else if (br.x - constants::ResizeMarkerSize <= x && x <= br.x)
		{
			return ResizeNode::BottomRight;
		}
	}

	return ResizeNode::None;
}

void ShapePresenter::UpdateView()
{
	if (m_selection.shape)
		UpdateSelectedShapeData();

	m_view->GetCanvas()->Clear();

	for (auto& shape : m_shapes)
	{
		if (m_selection.shape && shape->GetId() == m_selection.shape->GetId())
		{
			DrawShape(m_selection.topLeft, m_selection.bottomRight, shape);
		}
		else
		{
			DrawShape(shape->GetTopLeft(), shape->GetBottomRight(), shape);
		}
	}

	if (m_selection.shape)
	{
		DrawSelectionFrame(m_selection.topLeft, m_selection.bottomRight);
	}
}

void ShapePresenter::DrawShape(const common::Point& tl, const common::Point& br, const model::ShapeConstPtr& shape)
{
	switch (shape->GetType())
	{
	case model::ShapeType::Triangle:
		DrawTriangle(tl, br, shape);
		break;
	case model::ShapeType::Rectangle:
		DrawRectangle(tl, br, shape);
		break;
	case model::ShapeType::Ellipse:
		DrawEllipse(tl, br, shape);
		break;
	default:
		throw std::invalid_argument("Unknown shape type.");
	}
}

void ShapePresenter::DrawTriangle(const common::Point& tl, const common::Point& br, const model::ShapeConstPtr& shape)
{
	auto canvas = m_view->GetCanvas();
	std::vector<common::Point> points = {
		{ tl.x, br.y },
		{ (tl.x + br.x) / 2, tl.y },
		br
	};
	canvas->FillPolygon(points, shape->GetFillColor());
	canvas->DrawOutline(points, shape->GetBorderColor());
}

void ShapePresenter::DrawRectangle(const common::Point& tl, const common::Point& br, const model::ShapeConstPtr& shape)
{
	auto canvas = m_view->GetCanvas();
	std::vector<common::Point> points = {
		tl,
		{ br.x, tl.y },
		br,
		{ tl.x, br.y }
	};
	canvas->FillPolygon(points, shape->GetFillColor());
	canvas->DrawOutline(points, shape->GetBorderColor());
}

void ShapePresenter::DrawEllipse(const common::Point& tl, const common::Point& br, const model::ShapeConstPtr& shape)
{
	m_view->GetCanvas()->DrawEllipse(tl, br,
		shape->GetFillColor(), shape->GetBorderColor());
}

void ShapePresenter::DrawSelectionFrame(const common::Point& tl, const common::Point& br)
{
// clang-format off
	auto canvas = m_view->GetCanvas();
	// draw borders
	canvas->DrawOutline({
		tl, { br.x, tl.y },
		br, { tl.x, br.y }
	}, constants::SelectionFrameColor);
	// top left resize node
	canvas->FillPolygon({
		tl,
		{ tl.x + constants::ResizeMarkerSize, tl.y },
		{ tl.x + constants::ResizeMarkerSize, tl.y + constants::ResizeMarkerSize },
		{ tl.x, tl.y + constants::ResizeMarkerSize }
	}, constants::SelectionFrameColor);
	// top right resize node
	canvas->FillPolygon({
		{ br.x - constants::ResizeMarkerSize, tl.y },
		{ br.x, tl.y },
		{ br.x, tl.y + constants::ResizeMarkerSize },
		{ br.x - constants::ResizeMarkerSize, tl.y + constants::ResizeMarkerSize }
	}, constants::SelectionFrameColor);
	// bottom right resize node
	canvas->FillPolygon({
		{ br.x - constants::ResizeMarkerSize, br.y - constants::ResizeMarkerSize },
		{ br.x, br.y - constants::ResizeMarkerSize },
		br,
		{ br.x - constants::ResizeMarkerSize, br.y }
	}, constants::SelectionFrameColor);
	// bottom left resize node
	canvas->FillPolygon({
		{ tl.x, br.y - constants::ResizeMarkerSize },
		{ tl.x + constants::ResizeMarkerSize, br.y - constants::ResizeMarkerSize },
		{ tl.x + constants::ResizeMarkerSize, br.y },
		{ tl.x, br.y }
	}, constants::SelectionFrameColor);
// clang-format on
}

void ShapePresenter::OnShapeResize(float dx, float dy)
{
	switch (m_resizeNode)
	{
	case ResizeNode::None:
		throw std::invalid_argument("Resize node is 'None' value");
	case ResizeNode::TopLeft:
		m_selection.topLeft.x += dx;
		m_selection.topLeft.y += dy;
		if ((m_selection.bottomRight.x - m_selection.topLeft.x) < constants::MinShapeSize)
			m_selection.topLeft.x = m_selection.bottomRight.x - constants::MinShapeSize;
		if ((m_selection.bottomRight.y - m_selection.topLeft.y) < constants::MinShapeSize)
			m_selection.topLeft.y = m_selection.bottomRight.y - constants::MinShapeSize;
		break;
	case ResizeNode::TopRight:
		m_selection.bottomRight.x += dx;
		m_selection.topLeft.y += dy;
		if ((m_selection.bottomRight.x - m_selection.topLeft.x) < constants::MinShapeSize)
			m_selection.bottomRight.x = m_selection.topLeft.x + constants::MinShapeSize;
		if ((m_selection.bottomRight.y - m_selection.topLeft.y) < constants::MinShapeSize)
			m_selection.topLeft.y = m_selection.bottomRight.y - constants::MinShapeSize;
		break;
	case ResizeNode::BottomRight:
		m_selection.bottomRight.x += dx;
		m_selection.bottomRight.y += dy;
		if ((m_selection.bottomRight.x - m_selection.topLeft.x) < constants::MinShapeSize)
			m_selection.bottomRight.x = m_selection.topLeft.x + constants::MinShapeSize;
		if ((m_selection.bottomRight.y - m_selection.topLeft.y) < constants::MinShapeSize)
			m_selection.bottomRight.y = m_selection.topLeft.y + constants::MinShapeSize;
		break;
	case ResizeNode::BottomLeft:
		m_selection.topLeft.x += dx;
		m_selection.bottomRight.y += dy;
		if ((m_selection.bottomRight.x - m_selection.topLeft.x) < constants::MinShapeSize)
			m_selection.topLeft.x = m_selection.bottomRight.x - constants::MinShapeSize;
		if ((m_selection.bottomRight.y - m_selection.topLeft.y) < constants::MinShapeSize)
			m_selection.bottomRight.y = m_selection.topLeft.y + constants::MinShapeSize;
		break;
	default:
		throw std::invalid_argument("Unknown type of resize node");
	}
}

void ShapePresenter::OnShapeMove(float dx, float dy)
{
	m_selection.topLeft.x += dx;
	m_selection.topLeft.y += dy;
	m_selection.bottomRight.x += dx;
	m_selection.bottomRight.y += dy;
}

void ShapePresenter::CreateShape(model::ShapeType type)
{
	m_shapeComposition->AddShape(type);
}

void ShapePresenter::DeleteShape()
{
	if (m_selection.shape)
	{
		auto id = m_selection.shape->GetId();
		m_selection.shape.reset();
		m_shapeComposition->RemoveShape(id);
	}
}

void ShapePresenter::ChangeFillColor(const common::Color& color)
{
	if (m_selection.shape)
	{
		m_selection.shape->SetFillColor(color);
	}
}

void ShapePresenter::ChangeBorderColor(const common::Color& color)
{
	if (m_selection.shape)
	{
		m_selection.shape->SetBorderColor(color);
	}
}

void ShapePresenter::Undo()
{
	m_shapeComposition->Undo();
}

void ShapePresenter::Redo()
{
	m_shapeComposition->Redo();
}

bool presenter::ShapePresenter::CanUndo() const
{
	return m_shapeComposition->CanUndo();
}

bool presenter::ShapePresenter::CanRedo() const
{
	return m_shapeComposition->CanRedo();
}

bool presenter::ShapePresenter::IsShapeSelected() const
{
	return (bool)m_selection.shape;
}
