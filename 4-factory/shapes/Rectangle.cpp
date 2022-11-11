#include "Rectangle.h"

Rectangle::Rectangle(Point leftTop, Point rightBottom, Color color)
	: m_leftTop(std::move(leftTop))
	, m_rightBottom(std::move(rightBottom))
	, m_color(color)
{
}

void Rectangle::Draw(CanvasPtr& canvas) const
{
	canvas->SetColor(m_color);

	Point rightTop{ m_rightBottom.x, m_leftTop.y };
	Point leftBottom{ m_leftTop.x, m_rightBottom.y };

	canvas->DrawLine(m_leftTop, rightTop);
	canvas->DrawLine(rightTop, m_rightBottom);
	canvas->DrawLine(m_rightBottom, leftBottom);
	canvas->DrawLine(leftBottom, m_leftTop);
}

Color Rectangle::GetColor() const
{
	return m_color;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}
