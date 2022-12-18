#include "../../include/Model/ShapeStore.h"

void ShapeStore::ForEach(const std::function< void(const std::shared_ptr<const Shape>&) >& callback) const
{
	for (auto& [id, shape] : m_shapes)
	{
		callback(shape);
	}
}

void ShapeStore::ForEach(const std::function< void(std::shared_ptr<Shape>&) >& callback)
{
	for (auto& [id, shape] : m_shapes)
	{
		callback(shape);
	}
}

std::shared_ptr<Shape> ShapeStore::GetShapeById(size_t id)
{
	if (m_shapes.contains(id))
	{
		return m_shapes[id];
	}
	else
	{
		throw std::out_of_range("Failed to get shape by id: no shape with such id available.");
	}
}

std::shared_ptr<const Shape> ShapeStore::GetShapeById(size_t id) const
{
	if (m_shapes.contains(id))
	{
		return m_shapes.at(id);
	}
	else
	{
		throw std::out_of_range("Failed to get shape by id: no shape with such id available.");
	}
}

std::shared_ptr<Shape> ShapeStore::GetShapeByCoords(float x, float y)
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

std::shared_ptr<const Shape> ShapeStore::GetShapeByCoords(float x, float y) const
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

void ShapeStore::AddShape(const std::shared_ptr<Shape>& shape)
{
	if (!m_shapes.contains(shape->GetId()))
	{
		m_shapes.insert({ shape->GetId(), shape });
	}
	else
	{
		throw std::logic_error("Faild to add shape: shape with such id already exists.");
	}
}

void ShapeStore::RemoveShape(size_t id)
{
	if (m_shapes.contains(id))
	{
		m_shapes.erase(id);
	}
	else
	{
		throw std::out_of_range("Failed to remove shape by id: no shape with such id available.");
	}
}
