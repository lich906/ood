#include "Ellipse.h"

Ellipse::Ellipse(Point center, size_t horizontalRadius, size_t verticalRadius, Color color)
	: m_center(std::move(center))
	, m_horRadius(horizontalRadius)
	, m_vertRadius(verticalRadius)
	, m_color(color)
{
}

void Ellipse::Draw(CanvasPtr& canvas) const
{
	canvas->SetColor(m_color);
	canvas->DrawEllipse(m_center, m_horRadius, m_vertRadius);
}

Color Ellipse::GetColor() const
{
	return m_color;
}

Point Ellipse::GetCenter() const
{
	return m_center;
}

size_t Ellipse::GetHorizontalRadius() const
{
	return m_horRadius;
}

size_t Ellipse::GetVerticalRadius() const
{
	return m_vertRadius;
}
