#include "../../include/Presenter/ShapesPresenter.h"

ShapesPresenter::ShapesPresenter(ShapeStore& shapeStore)
	: m_shapeStore(shapeStore)
{
}

void ShapesPresenter::UpdateView(ICanvasPtr canvas)
{
}

bool ShapesPresenter::IsResizing() const
{
	return m_currentResizeNode != ResizeNode::None;
}

void ShapesPresenter::OnMouseDown(float x, float y)
{
	UpdateSelectedShape(x, y);

	if (m_selectedShapeId.has_value())
	{
		auto pressedResizeNode = GetPressedResizeNode(x, y);
	}
}

void ShapesPresenter::OnMouseUp(float dx, float dy)
{
}

void ShapesPresenter::OnMouseDrag(float dx, float dy)
{
}

void ShapesPresenter::StopResizing()
{
	m_currentResizeNode = ResizeNode::None;
}

void ShapesPresenter::ResetSelection()
{
	m_selectedShapeId.reset();
}

void ShapesPresenter::UpdateSelectedShape(float x, float y)
{
	if (auto shape = m_shapeStore.GetShapeByCoords(x, y))
	{
		m_selectedShapeId = shape->GetId();
	}
	else
	{
		m_selectedShapeId.reset();
	}
}

std::optional<ResizeNode> ShapesPresenter::GetPressedResizeNode(float x, float y) const
{
	if (!m_selectedShapeId)
	{
		return std::nullopt;
	}

	auto selectedShape = m_shapeStore.GetShapeById(*m_selectedShapeId);

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

	return std::nullopt;
}
