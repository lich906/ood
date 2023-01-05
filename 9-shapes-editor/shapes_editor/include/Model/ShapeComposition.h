#pragma once

#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <functional>
#include <string>
#include <set>

#include "IShapeComposition.h"
#include "Shape.h"
#include "Command/CommandHistory.h"
#include "Command/FunctionalCommand.h"

namespace model
{

class ShapeComposition : public IShapeComposition
{
public:
	ShapePtr GetShapeById(ShapeId id) override;
	ShapeConstPtr GetShapeById(ShapeId id) const override;
	ShapePtr FindShapeAtCoords(float x, float y) override;
	ShapeConstPtr FindShapeAtCoords(float x, float y) const override;
	void LiftShapeOnTop(ShapeId id);
	ShapeId AddShape(ShapeType type) override;
	void RemoveShape(ShapeId id) override;
	void Undo() override;
	void Redo() override;
	void RegisterOnChange(IShapeCompositionObserver* observer) override;

private:
	std::vector<ShapePtr> GetShapesSortedByZIndex() const;
	int GetHighestShapeZIndex() const;
	void NotifyObserversOnChange() const;

	std::unordered_map<ShapeId, std::shared_ptr<Shape>> m_shapes;
	CommandHistory m_commandHistory;
	std::set<IShapeCompositionObserver*> m_observers;
};

} // namespace model
