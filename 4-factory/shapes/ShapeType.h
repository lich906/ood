#ifndef SHAPE_TYPE_H
#define SHAPE_TYPE_H

#include <iostream>
#include <string>
#include <string_view>

enum class ShapeType
{
	Rectangle,
	Triangle,
	Ellipse,
	RegularPolygon,
};

namespace ShapeTypesStrings
{
constexpr std::string_view Rectangle = "rectangle";
constexpr std::string_view Triangle = "triangle";
constexpr std::string_view Ellipse = "ellipse";
constexpr std::string_view Polygon = "polygon";
}; // namespace ShapeTypesStrings

std::istream& operator>>(std::istream& stream, ShapeType& shapeType);

#endif // !SHAPE_TYPE_H
