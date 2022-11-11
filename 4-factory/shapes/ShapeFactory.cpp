#include "ShapeFactory.h"

ShapePtr ShapeFactory::CreateShape(const std::string& description) const
{
	std::istringstream stream(description);

	ShapeType shapeType = ShapeType::Ellipse;

	if (!(stream >> shapeType))
	{
		throw std::invalid_argument("Invalid shape type");
	}

	Color shapeColor = Color::Black;

	if (!(stream >> shapeColor))
	{
		throw std::invalid_argument("Invalid color string value");
	}

	switch (shapeType)
	{
	case ShapeType::Rectangle:
	{
		int leftTopX, leftTopY, rightBottomX, rightBottomY;
		if (!(stream >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY))
		{
			throw std::invalid_argument("Failed to read shape data");
		}
		return std::make_unique<Rectangle>(Point(leftTopX, leftTopY), Point(rightBottomX, rightBottomY), shapeColor);
	}
	case ShapeType::Triangle:
	{
		int vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;
		if (!(stream >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y))
		{
			throw std::invalid_argument("Failed to read shape data");
		}
		return std::make_unique<Triangle>(Point(vertex1X, vertex1Y), Point(vertex2X, vertex2Y), Point(vertex3X, vertex3Y), shapeColor);
	}
	case ShapeType::Ellipse:
	{
		int centerX, centerY;
		size_t width, height;
		if (!(stream >> centerX >> centerY >> width >> height))
		{
			throw std::invalid_argument("Failed to read shape data");
		}
		return std::make_unique<Ellipse>(Point(centerX, centerY), width, height, shapeColor);
	}
	case ShapeType::RegularPolygon:
	{
		size_t vertexCount, radius;
		int centerX, centerY;
		if (!(stream >> vertexCount >> centerX >> centerY >> radius))
		{
			throw std::invalid_argument("Failed to read shape data");
		}
		return std::make_unique<RegularPolygon>(vertexCount, Point(centerX, centerY), radius, shapeColor);
	}
	default:
		throw std::invalid_argument("Unknown shape type");
	}
}
