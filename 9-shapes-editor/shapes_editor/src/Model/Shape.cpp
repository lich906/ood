#include "../../include/Model/Shape.h"

Shape::Shape(ShapeType type, int zIndex)
	: m_type(type)
	, m_id(++lastId)
	, m_zIndex(zIndex)
{
}

size_t Shape::GetId() const
{
	return m_id;
}

ShapeType Shape::GetType() const
{
	return m_type;
}

Point Shape::GetTopLeft() const
{
	return m_topLeft;
}

void Shape::SetTopLeft(Point point)
{
	m_topLeft = std::move(point);
}

Point Shape::GetBottomRight() const
{
	return m_bottomRight;
}

void Shape::SetBottomRight(Point point)
{
	m_bottomRight = std::move(point);
}

Color Shape::GetFillColor() const
{
	return m_fillColor;
}

void Shape::SetFillColor(Color color)
{
	m_fillColor = std::move(color);
}

Color Shape::GetBorderColor() const
{
	return m_borderColor;
}

void Shape::SetBorderColor(Color color)
{
	m_borderColor = std::move(color);
}

int Shape::GetZIndex() const
{
	return m_zIndex;
}

void Shape::SetZIndex(int zIndex)
{
	m_zIndex = zIndex;
}
