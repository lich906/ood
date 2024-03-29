#include "../../include/Model/ShapeComposition.h"

using namespace model;

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

ShapePtr model::ShapeComposition::GetSelectedShape()
{
	if (m_selectedShapeId)
	{
		return m_shapes[*m_selectedShapeId];
	}

	return nullptr;
}

std::shared_ptr<IShape> ShapeComposition::FindShapeAtCoords(float x, float y)
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

void model::ShapeComposition::SelectShapeAtCoords(float x, float y)
{
	if (auto shape = FindShapeAtCoords(x, y))
	{
		m_selectedShapeId = shape->GetId();
	}
	else
	{
		m_selectedShapeId.reset();
	}
}

ShapeId ShapeComposition::AddShape(ShapeType type)
{
	auto shape = std::make_shared<Shape>(type, GetHighestShapeZIndex() + 1,
		[this](std::unique_ptr<Command>&& cmd) {
			m_commandHistory.AddAndExecute(std::move(cmd));
			NotifyObserversOnChange();
		});

	auto command = std::make_unique<FunctionalCommand>(
		[this, shape]() {
			m_shapes.insert({ shape->GetId(), shape });
			m_selectedShapeId = shape->GetId();
		},
		[this, id = shape->GetId()]() {
			m_shapes.erase(id);
			m_selectedShapeId.reset();
		});

	m_commandHistory.AddAndExecute(std::move(command));
	NotifyObserversOnChange();

	return shape->GetId();
}

void model::ShapeComposition::RemoveSelectedShape()
{
	if (m_selectedShapeId)
	{
		auto deletedShape = m_shapes[*m_selectedShapeId];

		auto command = std::make_unique<FunctionalCommand>(
			[this, id = *m_selectedShapeId]() {
				m_shapes.erase(id);
				m_selectedShapeId.reset();
			},
			[this, deletedShape]() {
				m_shapes.insert({ deletedShape->GetId(), deletedShape });
				m_selectedShapeId = deletedShape->GetId();
			});

		m_commandHistory.AddAndExecute(std::move(command));
		NotifyObserversOnChange();
	}
}

void ShapeComposition::Undo()
{
	if (m_commandHistory.CanUndo())
	{
		m_commandHistory.Undo();
		NotifyObserversOnChange();
	}
}

void ShapeComposition::Redo()
{
	if (m_commandHistory.CanRedo())
	{
		m_commandHistory.Redo();
		NotifyObserversOnChange();
	}
}

bool model::ShapeComposition::CanUndo() const
{
	return m_commandHistory.CanUndo();
}

bool model::ShapeComposition::CanRedo() const
{
	return m_commandHistory.CanRedo();
}

void model::ShapeComposition::RegisterOnChange(IShapeCompositionObserver* observer)
{
	m_observers.insert(observer);
}

std::vector<ShapeConstPtr> ShapeComposition::GetShapesSortedByZIndex() const
{
	std::vector<std::shared_ptr<Shape>> sortedShapes;

	for (auto& [id, shape] : m_shapes)
	{
		auto it = sortedShapes.begin();
		while (it != sortedShapes.end() && (*it)->GetZIndex() < shape->GetZIndex())
			++it;
		sortedShapes.insert(it, shape);
	}

	// must construct another vector since std::vector<Derived> cannot be implicitly converted to std::vector<Base>
	return { sortedShapes.begin(), sortedShapes.end() };
}

int ShapeComposition::GetHighestShapeZIndex() const
{
	int maxZIndex = -1;

	for (auto& [id, shape] : m_shapes)
	{
		int zIndex = shape->GetZIndex();
		if (zIndex > maxZIndex)
			maxZIndex = zIndex;
	}

	return maxZIndex;
}

void model::ShapeComposition::NotifyObserversOnChange() const
{
	for (auto& obs : m_observers)
	{
		obs->OnChange(GetShapesSortedByZIndex());
	}
}
