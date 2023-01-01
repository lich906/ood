#pragma once

#include "ShapeType.h"
#include "Point.h"
#include "Color.h"

typedef size_t ShapeId;

class IShape
{
public:
	virtual ~IShape() = default;

	virtual ShapeId GetId() const = 0;

	virtual ShapeType GetType() const = 0;

	virtual Point GetTopLeft() const = 0;
	virtual Point GetBottomRight() const = 0;

	virtual void Resize(const Point& topLeft, const Point& bottomRight) = 0;
	virtual void Move(float dx, float dy) = 0;

	virtual Color GetFillColor() const = 0;
	virtual void SetFillColor(Color color) = 0;

	virtual Color GetBorderColor() const = 0;
	virtual void SetBorderColor(Color color) = 0;
};
