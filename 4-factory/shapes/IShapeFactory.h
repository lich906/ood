#ifndef I_SHAPE_FACTORY_H
#define I_SHAPE_FACTORY_H

#include <string>

#include "IShape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual ShapePtr CreateShape(const std::string& description) const = 0;
};

typedef std::unique_ptr<IShapeFactory> ShapeFactoryPtr;

#endif // !I_SHAPE_FACTORY_H
