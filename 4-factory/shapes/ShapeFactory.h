#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <optional>
#include <sstream>
#include <string_view>

#include "Ellipse.h"
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "ShapeType.h"
#include "Triangle.h"

class ShapeFactory : public IShapeFactory
{
public:
	ShapePtr CreateShape(const std::string& description) const override;
};

#endif // !SHAPE_FACTORY_H
