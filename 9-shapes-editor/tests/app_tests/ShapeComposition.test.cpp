#include "pch.h"
#include "Model/ShapeComposition.h"

bool operator==(const common::Point& p1, const common::Point& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const common::Color& c1, const common::Color& c2)
{
	return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

TEST(AddShape, CheckDefaultValues)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Rectangle);
	auto shape = composition.GetShapeById(id);

	ASSERT_TRUE((bool)shape);
	ASSERT_EQ(shape->GetId(), id);
	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);
	ASSERT_EQ(shape->GetFillColor(), model::constants::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);
}

TEST(AddShape, UndoAddingShape)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Rectangle);

	ASSERT_TRUE((bool)composition.GetShapeById(id));

	composition.Undo();

	ASSERT_THROW(composition.GetShapeById(id), std::out_of_range);
}

TEST(AddShape, RedoAddingShape)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);

	composition.Undo();
	composition.Redo();

	ASSERT_TRUE((bool)composition.GetShapeById(id));
}


TEST(RemoveShape, RemoveShapeById)
{
	model::ShapeComposition composition;
	model::ShapeId id1 = composition.AddShape(model::ShapeType::Triangle);
	model::ShapeId id2 = composition.AddShape(model::ShapeType::Rectangle);

	composition.RemoveShape(id1);

	ASSERT_THROW(composition.GetShapeById(id1), std::out_of_range);
	ASSERT_TRUE((bool)composition.GetShapeById(id2));
}

TEST(RemoveShape, UndoRemoveShapeCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);

	composition.RemoveShape(id);
	composition.Undo();

	ASSERT_TRUE((bool)composition.GetShapeById(id));
}

TEST(RemoveShape, RedoRemoveShapeCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);

	composition.RemoveShape(id);
	composition.Undo();
	composition.Redo();

	ASSERT_THROW(composition.GetShapeById(id), std::out_of_range);
}


TEST(OnShapeMove, GetShapeAndMoveIt)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float dx = 40, dy = 20;
	auto shape = composition.GetShapeById(id);

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);

	shape->Move(dx, dy);

	ASSERT_EQ(shape->GetTopLeft().x, model::constants::TopLeftPoint.x + dx);
	ASSERT_EQ(shape->GetTopLeft().y, model::constants::TopLeftPoint.y + dy);
	ASSERT_EQ(shape->GetBottomRight().x, model::constants::BottomRightPoint.x + dx);
	ASSERT_EQ(shape->GetBottomRight().y, model::constants::BottomRightPoint.y + dy);
}

TEST(OnShapeMove, MoveShapeThenUndoCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float dx = 40, dy = 20;
	auto shape = composition.GetShapeById(id);

	shape->Move(dx, dy);
	composition.Undo();

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);
}

TEST(OnShapeMove, MoveShapeThenUndoAndRedoCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float dx = 40, dy = 20;
	auto shape = composition.GetShapeById(id);

	shape->Move(dx, dy);
	composition.Undo();
	composition.Redo();

	ASSERT_EQ(shape->GetTopLeft().x, model::constants::TopLeftPoint.x + dx);
	ASSERT_EQ(shape->GetTopLeft().y, model::constants::TopLeftPoint.y + dy);
	ASSERT_EQ(shape->GetBottomRight().x, model::constants::BottomRightPoint.x + dx);
	ASSERT_EQ(shape->GetBottomRight().y, model::constants::BottomRightPoint.y + dy);
}


TEST(OnShapeResize, ResizeShapeByTopLeftNode)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	float x = 10, y = 20;

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);

	shape->Resize(common::Point(x, y), shape->GetBottomRight());

	ASSERT_EQ(shape->GetTopLeft(), common::Point(x, y));
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);
}
