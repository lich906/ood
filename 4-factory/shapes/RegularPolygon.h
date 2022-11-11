#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

#include "IShape.h"

class RegularPolygon : public IShape
{
public:
	RegularPolygon(size_t vertexCount, Point center, int radius, Color color);

	void Draw(CanvasPtr& canvas) const override;

	Color GetColor() const override;

	size_t GetVertexCount() const;

	Point GetCenter() const;

	size_t GetRadius() const;

private:
	Point RotatePoint(const Point& c, double angle, Point p) const;

	size_t m_vertexCount;
	Point m_center;
	int m_radius;
	Color m_color;
};

#endif // !REGULAR_POLYGON_H
