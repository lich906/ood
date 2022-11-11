#include "ShapeType.h"

std::istream& operator>>(std::istream& stream, ShapeType& shapeType)
{
	std::string str;
	stream >> str;

	if (str == ShapeTypesStrings::Rectangle)
	{
		shapeType = ShapeType::Rectangle;
	}
	else if (str == ShapeTypesStrings::Triangle)
	{
		shapeType = ShapeType::Triangle;
	}
	else if (str == ShapeTypesStrings::Ellipse)
	{
		shapeType = ShapeType::Ellipse;
	}
	else if (str == ShapeTypesStrings::Polygon)
	{
		shapeType = ShapeType::RegularPolygon;
	}
	else
	{
		stream.setstate(std::ios::failbit);
	}

	return stream;
}
