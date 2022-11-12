#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "IShape.h"

class Triangle : public IShape
{
public:
	Triangle(Point v1, Point v2, Point v3, Color color);

	void Draw(ICanvas* canvas) const override;

	Color GetColor() const override;

	Point GetVertex1() const;

	Point GetVertex2() const;

	Point GetVertex3() const;

private:
	std::array<Point, 3> m_vertexes;
	Color m_color;
};

#endif // !TRIANGLE_H
