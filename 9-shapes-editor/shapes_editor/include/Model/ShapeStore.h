#pragma once

#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <functional>

#include "Shape.h"

class ShapeStore
{
public:
	/*
	* Calls callback function for each stored shape. Const version.
	*/
	void ForEach(const std::function<void(const std::shared_ptr<const Shape>&)>& callback) const;

	/*
	* Calls callback function for each stored shape.
	*/
	void ForEach(const std::function<void(std::shared_ptr<Shape>&)>& callback);

	/*
	* @throws std::out_of_range if shape with 'id' not found
	*/
	std::shared_ptr<Shape> GetShapeById(size_t id);

	/*
	* @throws std::out_of_range if shape with 'id' not found
	*/
	std::shared_ptr<const Shape> GetShapeById(size_t id) const;

	/*
	* @throws std::logic_error if there is no shape at x, y
	*/
	std::shared_ptr<Shape> GetShapeByCoords(float x, float y);

	/*
	* @throws std::logic_error if there is no shape at x, y
	*/
	std::shared_ptr<const Shape> GetShapeByCoords(float x, float y) const;

	void AddShape(const std::shared_ptr<Shape>& shape);

	void RemoveShape(size_t id);

private:
	std::unordered_map<size_t, std::shared_ptr<Shape>> m_shapes;

	int m_maxZIndex = 0;
};
