#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(size_t vertexCount, Point center, int radius, Color color)
	: m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
	, m_color(color)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Invalid radius negative value.");
	}
}

void RegularPolygon::Draw(ICanvas* canvas) const
{
	canvas->SetColor(m_color);

	Point farRightPoint{ m_center.x + m_radius, m_center.y };
	double angle = (M_PI * 2) / m_vertexCount;

	Point from = farRightPoint;
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		Point to = RotatePoint(m_center, angle, from);
		canvas->DrawLine(from, to);
		from = to;
	}
}

Color RegularPolygon::GetColor() const
{
	return m_color;
}

size_t RegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point RegularPolygon::GetCenter() const
{
	return m_center;
}

size_t RegularPolygon::GetRadius() const
{
	return m_radius;
}

Point RegularPolygon::RotatePoint(const Point& center, double angle, Point p) const
{
	double s = sin(angle);
	double c = cos(angle);

	p.x -= center.x;
	p.y -= center.y;

	double xnew = p.x * c - p.y * s;
	double ynew = p.x * s + p.y * c;

	p.x = round(xnew + center.x);
	p.y = round(ynew + center.y);

	return p;
}
