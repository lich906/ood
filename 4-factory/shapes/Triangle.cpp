#include "Triangle.h"

Triangle::Triangle(Point v1, Point v2, Point v3, Color color)
	: m_vertexes({std::move(v1), std::move(v2), std::move(v3)})
	, m_color(color)
{
}

void Triangle::Draw(ICanvas* canvas) const
{
	canvas->SetColor(m_color);
	canvas->DrawLine(m_vertexes[0], m_vertexes[1]);
	canvas->DrawLine(m_vertexes[1], m_vertexes[2]);
	canvas->DrawLine(m_vertexes[2], m_vertexes[0]);
}

Color Triangle::GetColor() const
{
	return m_color;
}

Point Triangle::GetVertex1() const
{
	return m_vertexes[0];
}

Point Triangle::GetVertex2() const
{
	return m_vertexes[1];
}

Point Triangle::GetVertex3() const
{
	return m_vertexes[2];
}
