#pragma once

#include <type_traits>

#include "ShapeType.h"
#include "Point.h"
#include "Color.h"
#include "Defaults.h"

class Shape
{
public:
	Shape(ShapeType type, int zIndex);

	size_t GetId() const;

	ShapeType GetType() const;

	Point GetTopLeft() const;
	void SetTopLeft(Point point);

	Point GetBottomRight() const;
	void SetBottomRight(Point point);

	Color GetFillColor() const;
	void SetFillColor(Color color);

	Color GetBorderColor() const;
	void SetBorderColor(Color color);

	int GetZIndex() const;
	void SetZIndex(int zIndex);

private:
	ShapeType m_type;
	size_t m_id;
	Point m_topLeft = Defaults::TopLeftPoint;
	Point m_bottomRight = Defaults::BottomRightPoint;
	Color m_fillColor = Defaults::FillColor;
	Color m_borderColor = Defaults::BorderColor;
	int m_zIndex;

	inline static size_t lastId = 0;
};
