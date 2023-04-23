#include "Presenter/ShapePresenter.h"

using namespace presenter;

ShapePresenter::ShapePresenter(model::IShapeComposition* shapeComposition, view::IView* view)
	: m_shapeComposition(shapeComposition)
	, m_view(view)
{
	m_shapeComposition->RegisterOnChange(this);
}

void ShapePresenter::OnChange(const std::vector<model::ShapeConstPtr>& shapes)
{
	m_shapes = shapes;

	if (auto shape = m_shapeComposition->GetSelectedShape())
	{
		UpdateSelectionBoundings(shape->GetTopLeft(), shape->GetBottomRight());
	}
}

void ShapePresenter::OnMouseDown()
{
	common::Point pos = m_view->GetMousePos();
	m_shapeComposition->SelectShapeAtCoords(pos.x, pos.y);

	if (auto shape = m_shapeComposition->GetSelectedShape())
	{
		UpdateSelectionBoundings(shape->GetTopLeft(), shape->GetBottomRight());
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

	UpdateView();
}

void ShapePresenter::OnMouseUp()
{
	auto shape = m_shapeComposition->GetSelectedShape();
	if (shape &&
		(m_selection.topLeft != shape->GetTopLeft() ||
		m_selection.bottomRight != shape->GetBottomRight()))
	{
		shape->Resize(m_selection.topLeft, m_selection.bottomRight);
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
	if (m_shapeComposition->GetSelectedShape())
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

void presenter::ShapePresenter::UpdateSelectionBoundings(const common::Point& topLeft, const common::Point& bottomRight)
{
	m_selection.topLeft = topLeft;
	m_selection.bottomRight = bottomRight;
}

ResizeNode ShapePresenter::GetPressedResizeNode(float x, float y) const
{
	auto selectedShape = m_shapeComposition->GetSelectedShape();
	if (!selectedShape)
	{
		return ResizeNode::None;
	}

	auto tl = selectedShape->GetTopLeft();
	auto br = selectedShape->GetBottomRight();

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

void ShapePresenter::FixShapeOutOfCanvasOverflow()
{
	m_selection.topLeft.x = std::max(m_selection.topLeft.x, 0.0f);
	m_selection.topLeft.y = std::max(m_selection.topLeft.y, 0.0f);
	m_selection.bottomRight.x = std::min(m_selection.bottomRight.x, m_view->GetCanvas()->GetWidth());
	m_selection.bottomRight.y = std::min(m_selection.bottomRight.y, m_view->GetCanvas()->GetHeight());
}

void ShapePresenter::UpdateView()
{
	auto selectedShape = m_shapeComposition->GetSelectedShape();
	if (selectedShape)
	{
		m_view->SetSelectedShapeData({ selectedShape->GetId(),
			m_selection.topLeft, m_selection.bottomRight,
			selectedShape->GetFillColor(), selectedShape->GetBorderColor() });
	}

	m_view->GetCanvas()->Clear();

	for (auto& shape : m_shapes)
	{
		if (selectedShape == shape && (m_isMoving || m_resizeNode != ResizeNode::None))
		{
			DrawShape(m_selection.topLeft, m_selection.bottomRight, shape);
		}
		else
		{
			DrawShape(shape->GetTopLeft(), shape->GetBottomRight(), shape);
		}
	}

	if (selectedShape)
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

	FixShapeOutOfCanvasOverflow();
}

void ShapePresenter::OnShapeMove(float dx, float dy)
{
	if (m_selection.topLeft.x + dx < 0 || m_selection.bottomRight.x + dx > m_view->GetCanvas()->GetWidth()) dx = 0.0f;
	if (m_selection.topLeft.y + dy < 0 || m_selection.bottomRight.y + dy > m_view->GetCanvas()->GetHeight()) dy = 0.0f;

	m_selection.topLeft.x += dx;
	m_selection.topLeft.y += dy;
	m_selection.bottomRight.x += dx;
	m_selection.bottomRight.y += dy;
}

void ShapePresenter::CreateShape(model::ShapeType type)
{
	m_shapeComposition->AddShape(type);
	UpdateSelectionBoundings(m_shapeComposition->GetSelectedShape()->GetTopLeft(),
		m_shapeComposition->GetSelectedShape()->GetBottomRight());
	UpdateView();
}

void ShapePresenter::DeleteShape()
{
	m_shapeComposition->RemoveSelectedShape();
	UpdateView();
}

void ShapePresenter::ChangeFillColor(const common::Color& color)
{
	if (auto shape = m_shapeComposition->GetSelectedShape())
	{
		shape->SetFillColor(color);
	}
	UpdateView();
}

void ShapePresenter::ChangeBorderColor(const common::Color& color)
{
	if (auto shape = m_shapeComposition->GetSelectedShape())
	{
		shape->SetBorderColor(color);
	}
	UpdateView();
}

void ShapePresenter::Undo()
{
	m_shapeComposition->Undo();
	UpdateView();
}

void ShapePresenter::Redo()
{
	m_shapeComposition->Redo();
	UpdateView();
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
	return (bool)m_shapeComposition->GetSelectedShape();
}
