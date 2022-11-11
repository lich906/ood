#include "StreamCanvas.h"

std::ostream& operator<<(std::ostream& stream, Color color)
{
	switch (color)
	{
	case Color::Green:
		return stream << "green";
	case Color::Red:
		return stream << "red";
	case Color::Blue:
		return stream << "blue";
	case Color::Yellow:
		return stream << "yellow";
	case Color::Pink:
		return stream << "pink";
	case Color::Black:
		return stream << "black";
	default:
		return stream;
	}
}

std::ostream& operator<<(std::ostream& stream, Point point)
{
	return stream << point.x << ',' << point.y;
}

StreamCanvas::StreamCanvas(std::ostream& stream)
	: m_stream(stream)
{
}

void StreamCanvas::SetColor(Color color)
{
	m_color = color;
	m_stream << "color was set to " << m_color << std::endl;
}

void StreamCanvas::DrawLine(Point from, Point to)
{
	m_stream << "drawing line from " << from << " to " << to << " with color " << m_color << std::endl;
}

void StreamCanvas::DrawEllipse(Point center, size_t width, size_t height)
{
	m_stream << "drawing ellipse with center in " << center << " width " << width << " height " << height << " with color " << m_color << std::endl;
}
