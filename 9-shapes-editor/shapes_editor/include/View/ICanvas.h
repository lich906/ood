#pragma once

#include <vector>
#include <memory>

#include "..\Model\Point.h"
#include "..\Model\Color.h"

struct ICanvas
{
	virtual ~ICanvas() = default;
	virtual void FillPolygon(const std::vector<Point>& points, const Color& fillColor) = 0;
	virtual void DrawLine(const Point& from, const Point& to, const Color& color) = 0;
	virtual void DrawEllipse(Point leftTop, Point bottomRight, const Color& fillColor, const Color& borderColor) = 0;
	virtual void DrawResizeFrame(const Point& leftTop, const Point& bottomRight) = 0;
};

using ICanvasPtr = std::shared_ptr<ICanvas>;
