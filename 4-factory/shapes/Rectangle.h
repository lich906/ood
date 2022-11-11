#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "IShape.h"

class Rectangle : public IShape
{
public:
	Rectangle(Point leftTop, Point rightBottom, Color color);

	void Draw(CanvasPtr& canvas) const override;

	Color GetColor() const override;

	Point GetLeftTop() const;

	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
	Color m_color;
};

#endif // !RECTANGLE_H
