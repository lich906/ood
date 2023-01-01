#include "pch.h"
#include "Model/ShapeComposition.h"

bool operator==(const Point& p1, const Point& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const Color& c1, const Color& c2)
{
	return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

TEST(AddShape, CheckDefaultValues)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Rectangle); // id 1
	auto shape = composition.GetShapeById(1);

	ASSERT_TRUE((bool)shape);
	ASSERT_EQ(shape->GetTopLeft(), Defaults::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), Defaults::BottomRightPoint);
	ASSERT_EQ(shape->GetFillColor(), Defaults::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), Defaults::BorderColor);
}

TEST(AddShape, UndoAddingShape)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Rectangle); // id 2

	ASSERT_TRUE((bool)composition.GetShapeById(2));

	composition.Undo();

	ASSERT_THROW(composition.GetShapeById(2), std::out_of_range);
}

TEST(AddShape, RedoAddingShape)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Triangle); // id 3

	composition.Undo();
	composition.Redo();

	ASSERT_TRUE((bool)composition.GetShapeById(3));
}

TEST(RemoveShape, RemoveShapeById)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Triangle); // id 4
	composition.AddShape(ShapeType::Rectangle); // id 5

	composition.RemoveShape(4);

	ASSERT_THROW(composition.GetShapeById(4), std::out_of_range);
	ASSERT_TRUE((bool)composition.GetShapeById(5));
}

TEST(RemoveShape, UndoRemoveShapeCommand)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Triangle); // id 6

	composition.RemoveShape(6);
	composition.Undo();

	ASSERT_TRUE((bool)composition.GetShapeById(6));
}

TEST(RemoveShape, RedoRemoveShapeCommand)
{
	ShapeComposition composition;
	composition.AddShape(ShapeType::Triangle); // id 7

	composition.RemoveShape(7);
	composition.Undo();
	composition.Redo();

	ASSERT_THROW(composition.GetShapeById(7), std::out_of_range);
}
