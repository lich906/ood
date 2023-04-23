#include "pch.h"
#include "Model/ShapeComposition.h"

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


TEST(SelectShape, SelectShapeAtCoords)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) / 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) / 2;
	composition.SelectShapeAtCoords(x, y);

	auto selectedShape = composition.GetSelectedShape();

	ASSERT_TRUE((bool)selectedShape);
	ASSERT_EQ(composition.GetShapeById(id), selectedShape);
}

TEST(SelectShape, SelectShapeOutOfShapeCoords)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) * 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) * 2;
	composition.SelectShapeAtCoords(x, y);

	auto selectedShape = composition.GetSelectedShape();

	ASSERT_FALSE((bool)selectedShape);
}

TEST(SelectShape, SelectSecondAddedShapeAtDefaultPosition)
{
	model::ShapeComposition composition;
	model::ShapeId id1 = composition.AddShape(model::ShapeType::Triangle);
	model::ShapeId id2 = composition.AddShape(model::ShapeType::Rectangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) / 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) / 2;
	composition.SelectShapeAtCoords(x, y);

	auto selectedShape = composition.GetSelectedShape();

	ASSERT_TRUE((bool)selectedShape);
	ASSERT_EQ(composition.GetShapeById(id2), selectedShape);
}


TEST(RemoveShape, RemoveSelectedShape)
{
	model::ShapeComposition composition;
	model::ShapeId id1 = composition.AddShape(model::ShapeType::Triangle);
	model::ShapeId id2 = composition.AddShape(model::ShapeType::Rectangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) / 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) / 2;

	composition.SelectShapeAtCoords(x, y);

	composition.RemoveSelectedShape();

	ASSERT_THROW(composition.GetShapeById(id2), std::out_of_range);
	ASSERT_TRUE((bool)composition.GetShapeById(id1));
}

TEST(RemoveShape, UndoRemoveShapeCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) / 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) / 2;

	composition.SelectShapeAtCoords(x, y);

	composition.RemoveSelectedShape();
	composition.Undo();

	ASSERT_TRUE((bool)composition.GetShapeById(id));
}

TEST(RemoveShape, RedoRemoveShapeCommand)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	float x = (model::constants::BottomRightPoint.x - model::constants::TopLeftPoint.x) / 2;
	float y = (model::constants::BottomRightPoint.y - model::constants::TopLeftPoint.y) / 2;

	composition.SelectShapeAtCoords(x, y);

	composition.RemoveSelectedShape();
	composition.Undo();
	composition.Redo();

	ASSERT_THROW(composition.GetShapeById(id), std::out_of_range);
}


TEST(ResizeShape, ResizeShapeTest)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	float x1 = 10, y1 = 20, x2 = 30, y2 = 50;

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);

	shape->Resize(common::Point(x1, y1), common::Point(x2, y2));

	ASSERT_EQ(shape->GetTopLeft(), common::Point(x1, y1));
	ASSERT_EQ(shape->GetBottomRight(), common::Point(x2, y2));
}

TEST(ResizeShape, UndoShapeResizing)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	float x1 = 10, y1 = 20, x2 = 30, y2 = 50;

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);

	shape->Resize(common::Point(x1, y1), common::Point(x2, y2));
	composition.Undo();

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);
}

TEST(ResizeShape, RedoShapeResizing)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	float x1 = 10, y1 = 20, x2 = 30, y2 = 50;

	ASSERT_EQ(shape->GetTopLeft(), model::constants::TopLeftPoint);
	ASSERT_EQ(shape->GetBottomRight(), model::constants::BottomRightPoint);

	shape->Resize(common::Point(x1, y1), common::Point(x2, y2));
	composition.Undo();
	composition.Redo();

	ASSERT_EQ(shape->GetTopLeft(), common::Point(x1, y1));
	ASSERT_EQ(shape->GetBottomRight(), common::Point(x2, y2));
}


TEST(ChangeColors, ChangeFillAndBorderColor)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	common::Color fillColor = { 1.0f, 2.0f, 3.0f, 4.0f }, borderColor = { 4.0f, 3.0f, 2.0f, 1.0f };

	ASSERT_EQ(shape->GetFillColor(), model::constants::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);

	shape->SetFillColor(fillColor);
	shape->SetBorderColor(borderColor);

	ASSERT_EQ(shape->GetFillColor(), fillColor);
	ASSERT_EQ(shape->GetBorderColor(), borderColor);
}

TEST(ChangeColors, UndoColorChanges)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	common::Color fillColor = { 1.0f, 2.0f, 3.0f, 4.0f }, borderColor = { 4.0f, 3.0f, 2.0f, 1.0f };

	ASSERT_EQ(shape->GetFillColor(), model::constants::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);

	shape->SetFillColor(fillColor);
	shape->SetBorderColor(borderColor);

	composition.Undo();

	ASSERT_EQ(shape->GetFillColor(), fillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);

	composition.Undo();

	ASSERT_EQ(shape->GetFillColor(), model::constants::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);
}

TEST(ChangeColors, RedoColorChanges)
{
	model::ShapeComposition composition;
	model::ShapeId id = composition.AddShape(model::ShapeType::Triangle);
	auto shape = composition.GetShapeById(id);
	common::Color fillColor = { 1.0f, 2.0f, 3.0f, 4.0f }, borderColor = { 4.0f, 3.0f, 2.0f, 1.0f };

	ASSERT_EQ(shape->GetFillColor(), model::constants::FillColor);
	ASSERT_EQ(shape->GetBorderColor(), model::constants::BorderColor);

	shape->SetFillColor(fillColor);
	shape->SetBorderColor(borderColor);

	composition.Undo();
	composition.Undo();

	composition.Redo();
	composition.Redo();

	ASSERT_EQ(shape->GetFillColor(), fillColor);
	ASSERT_EQ(shape->GetBorderColor(), borderColor);
}
