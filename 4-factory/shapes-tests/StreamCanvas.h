#pragma once

#include <sstream>

#include "Color.h"
#include "Point.hpp"
#include "ICanvas.h"

std::ostream& operator<<(std::ostream& stream, Color color);

std::ostream& operator<<(std::ostream& stream, Point point);

class StreamCanvas : public ICanvas
{
public:
	StreamCanvas(std::ostream& stream);

	/*
		Prints message:
		"color was set to {Color}"
	*/
	void SetColor(Color color) override;

	/*
		Prints message:
		"drawing line from {Point} to {Point} with color {Color}"
	*/
	void DrawLine(Point from, Point to) override;

	/*
		Prints message:
		"drawing ellipse with center in {Point} width {size_t} height {size_t} with color {Color}"
	*/
	void DrawEllipse(Point center, size_t width, size_t height) override;

private:
	std::ostream& m_stream;
	Color m_color = Color::Black;
};