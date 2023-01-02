#include "../../include/Presenter/ShapesPresenter.h"

ShapePresenter::ShapePresenter(const ShapeComposition& shapeStore, Selection& selection)
	: m_shapeComposition(shapeStore)
	, m_selection(selection)
{
}

void ShapePresenter::UpdatePresentation(const std::vector<std::shared_ptr<Shape>>& shapes)
{
}

void ShapePresenter::OnMouseDown(float x, float y)
{
	UpdateShapeSelection(x, y);

	if (m_selection)
	{
		auto pressedResizeNode = GetPressedResizeNode(x, y);
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

void ShapePresenter::OnMouseUp(float dx, float dy)
{
	if (m_resizeNode != ResizeNode::None)
	{
		m_resizeNode = ResizeNode::None;
	}
	if (m_isMoving)
	{
		m_isMoving = false;
	}
	m_dragOffset.x = 0;
	m_dragOffset.y = 0;
}

void ShapePresenter::OnMouseDrag(float dx, float dy)
{
	if (m_isMoving || m_resizeNode != ResizeNode::None)
	{
		m_dragOffset.x = dx;
		m_dragOffset.y = dy;
	}
}

void ShapePresenter::UpdateShapeSelection(float x, float y)
{
	if (auto shape = m_shapeComposition.FindShapeByCoords(x, y))
	{
		if (m_selection.GetSelectedShape()->GetId() != shape->GetId())
		{
			m_selection.SetSelectedShape(shape);
		}
	}
	else
	{
		m_selection.Reset();
	}
}

ResizeNode ShapePresenter::GetPressedResizeNode(float x, float y) const
{
	if (!m_selection)
	{
		return ResizeNode::None;
	}

	auto selectedShape = m_shapeComposition.GetShapeById(m_selection.GetSelectedShape()->GetId());

	auto topLeft = selectedShape->GetTopLeft();
	auto bottomRight = selectedShape->GetBottomRight();

	if (topLeft.y <= y && y <= topLeft.y + constants::ResizeMarkerSize) // maybe top left or top right
	{
		if (topLeft.x <= x && x <= topLeft.x + constants::ResizeMarkerSize)
		{
			return ResizeNode::TopLeft;
		}
		else if (bottomRight.x - constants::ResizeMarkerSize <= x && x <= bottomRight.x)
		{
			return ResizeNode::TopRight;
		}
	}
	else if (bottomRight.y - constants::ResizeMarkerSize <= y && y <= bottomRight.y) // maybe bottom left or bottom right
	{
		if (topLeft.x <= x && x <= topLeft.x + constants::ResizeMarkerSize)
		{
			return ResizeNode::BottomLeft;
		}
		else if (bottomRight.x - constants::ResizeMarkerSize <= x && x <= bottomRight.x)
		{
			return ResizeNode::BottomRight;
		}
	}

	return ResizeNode::None;
}

void ShapePresenter::DrawShape(const Shape& shape, ICanvasPtr canvas)
{
}

void ShapePresenter::DrawSelectionFrame(const Point& leftTop, const Point& bottomRight, ICanvasPtr canvas)
{
}
