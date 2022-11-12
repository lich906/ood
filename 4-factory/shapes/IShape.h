#ifndef I_SHAPE_H
#define I_SHAPE_H

#include "Color.h"
#include "ICanvas.h"

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void Draw(ICanvas* canvas) const = 0;
	virtual Color GetColor() const = 0;
};

typedef std::unique_ptr<IShape> ShapePtr;

#endif // !I_SHAPE_H
