#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "IShape.h"

class Ellipse : public IShape
{
public:
	Ellipse(Point center, size_t horizontalRadius, size_t verticalRadius, Color color);

	void Draw(ICanvas* canvas) const;

	Color GetColor() const;

	Point GetCenter() const;

	size_t GetHorizontalRadius() const;

	size_t GetVerticalRadius() const;

private:
	Point m_center;
	size_t m_horRadius;
	size_t m_vertRadius;
	Color m_color;
};

#endif // !ELLIPSE_H
