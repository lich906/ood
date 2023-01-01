#include "../../include/Model/ShapeComposition.h"

std::shared_ptr<IShape> ShapeComposition::GetShapeById(ShapeId id)
{
	if (m_shapes.contains(id))
	{
		return m_shapes[id];
	}
	else
	{
		throw std::out_of_range("Shape with id '" + std::to_string(id) + "' not found.");
	}
}

std::shared_ptr<const IShape> ShapeComposition::GetShapeById(ShapeId id) const
{
	if (m_shapes.contains(id))
	{
		return m_shapes.at(id);
	}
	else
	{
		throw std::out_of_range("Shape with id '" + std::to_string(id) + "' not found.");
	}
}

std::shared_ptr<IShape> ShapeComposition::FindShapeByCoords(float x, float y)
{
	std::shared_ptr<Shape> shapePtr;
	int maxZIndex = -INT_MIN;
	std::for_each(m_shapes.begin(), m_shapes.end(),
		[&](std::unordered_map<size_t, std::shared_ptr<Shape>>::value_type& node) {
		auto& shape = node.second;
		if (shape->GetTopLeft().x <= x && x <= shape->GetBottomRight().x && 
			shape->GetTopLeft().y <= y && y <= shape->GetBottomRight().y && 
			shape->GetZIndex() > maxZIndex)
		{
			shapePtr = shape;
			maxZIndex = shape->GetZIndex();
		}
	});

	return shapePtr;
}

std::shared_ptr<const IShape> ShapeComposition::FindShapeByCoords(float x, float y) const
{
	std::shared_ptr<const Shape> shapePtr;
	int maxZIndex = -INT_MIN;
	std::for_each(m_shapes.begin(), m_shapes.end(),
		[&](const std::unordered_map<size_t, std::shared_ptr<Shape>>::value_type& node) {
		auto& shape = node.second;
		if (shape->GetTopLeft().x <= x && x <= shape->GetBottomRight().x && 
			shape->GetTopLeft().y <= y && y <= shape->GetBottomRight().y && 
			shape->GetZIndex() > maxZIndex)
		{
			shapePtr = shape;
			maxZIndex = shape->GetZIndex();
		}
	});

	return shapePtr;
}

void ShapeComposition::LiftShapeOnTop(ShapeId id)
{
	if (m_shapes.contains(id))
	{
		m_shapes[id]->SetZIndex(GetHighestShapeZIndex() + 1);
	}
	else
	{
		throw std::out_of_range("Shape with id '" + std::to_string(id) + "' not found.");
	}
}

ShapeId ShapeComposition::AddShape(ShapeType type)
{
	auto shape = std::make_shared<Shape>(type, GetHighestShapeZIndex() + 1,
		[this](std::unique_ptr<Command>&& cmd) {
			m_commandHistory.AddAndExecute(std::move(cmd));
		});

	auto command = std::make_unique<FunctionalCommand>(
		[this, shape]() {
			m_shapes.insert({ shape->GetId(), shape });
		},
		[this, id = shape->GetId()]() {
			m_shapes.erase(id);
		});

	m_commandHistory.AddAndExecute(std::move(command));

	return shape->GetId();
}

void ShapeComposition::RemoveShape(ShapeId id)
{
	if (m_shapes.contains(id))
	{
		auto deletedShape = m_shapes[id];

		auto command = std::make_unique<FunctionalCommand>(
			[this, id]() {
				m_shapes.erase(id);
			},
			[this, deletedShape]() {
				m_shapes.insert({deletedShape->GetId(), deletedShape});
			});

		m_commandHistory.AddAndExecute(std::move(command));
	}
	else
	{
		throw std::out_of_range("Failed to remove shape by id: no shape with such id available.");
	}

}

void ShapeComposition::Undo()
{
	if (m_commandHistory.CanUndo())
	{
		m_commandHistory.Undo();
	}
}

void ShapeComposition::Redo()
{
	if (m_commandHistory.CanRedo())
	{
		m_commandHistory.Redo();
	}
}

std::vector<std::shared_ptr<const Shape>> ShapeComposition::GetShapesSortedByZIndex() const
{
	std::vector<std::shared_ptr<const Shape>> sortedShapes;

	for (auto& [id, shape] : m_shapes)
	{
		auto it = sortedShapes.begin();
		while (it != sortedShapes.end() && (*it)->GetZIndex() < shape->GetZIndex())
			++it;
		sortedShapes.insert(it, shape);
	}

	return sortedShapes;
}

int ShapeComposition::GetHighestShapeZIndex() const
{
	int resZIndex = -1;

	for (auto& [id, shape] : m_shapes)
	{
		int zIndex = shape->GetZIndex();
		if (zIndex > resZIndex)
			resZIndex = zIndex;
	}

	return resZIndex;
}
