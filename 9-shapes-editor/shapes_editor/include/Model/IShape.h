#pragma once

#include "ShapeType.h"
#include "Common/Point.h"
#include "Common/Color.h"

namespace model
{

using ShapeId = size_t;

class IShape
{
public:
	virtual ~IShape() = default;

	virtual ShapeId GetId() const = 0;

	virtual ShapeType GetType() const = 0;

	virtual common::Point GetTopLeft() const = 0;
	virtual common::Point GetBottomRight() const = 0;

	virtual void Resize(const common::Point& topLeft, const common::Point& bottomRight) = 0;

	virtual common::Color GetFillColor() const = 0;
	virtual void SetFillColor(common::Color color) = 0;

	virtual common::Color GetBorderColor() const = 0;
	virtual void SetBorderColor(common::Color color) = 0;
};

using ShapePtr = std::shared_ptr<IShape>;
using ShapeConstPtr = std::shared_ptr<const IShape>;

} // namespace MyNamespace