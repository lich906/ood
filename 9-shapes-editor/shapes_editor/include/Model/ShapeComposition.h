#pragma once

#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <functional>
#include <string>

#include "IShapeComposition.h"
#include "Shape.h"
#include "Command/CommandHistory.h"
#include "Command/FunctionalCommand.h"

class ShapeComposition : public IShapeComposition
{
public:
	std::shared_ptr<IShape> GetShapeById(ShapeId id) override;
	std::shared_ptr<const IShape> GetShapeById(ShapeId id) const override;
	std::shared_ptr<IShape> FindShapeByCoords(float x, float y) override;
	std::shared_ptr<const IShape> FindShapeByCoords(float x, float y) const override;
	void LiftShapeOnTop(ShapeId id);
	ShapeId AddShape(ShapeType type) override;
	void RemoveShape(ShapeId id) override;
	void Undo() override;
	void Redo() override;

private:
	std::vector<std::shared_ptr<const Shape>> GetShapesSortedByZIndex() const;
	int GetHighestShapeZIndex() const;

	std::unordered_map<size_t, std::shared_ptr<Shape>> m_shapes;
	CommandHistory m_commandHistory;
};
