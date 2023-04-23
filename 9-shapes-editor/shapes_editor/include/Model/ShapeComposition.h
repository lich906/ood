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
	// <<interface>> IShapeComposition
	ShapePtr GetShapeById(ShapeId id) override;
	ShapePtr GetSelectedShape();
	void SelectShapeAtCoords(float x, float y) override;
	ShapeId AddShape(ShapeType type) override;
	void RemoveSelectedShape() override;
	void Undo() override;
	void Redo() override;
	bool CanUndo() const override;
	bool CanRedo() const override;
	void RegisterOnChange(IShapeCompositionObserver* observer) override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	ShapePtr FindShapeAtCoords(float x, float y);
	std::vector<ShapeConstPtr> GetShapesSortedByZIndex() const;
	int GetHighestShapeZIndex() const;
	void NotifyObserversOnChange() const;

	std::optional<ShapeId> m_selectedShapeId;
	std::unordered_map<ShapeId, std::shared_ptr<Shape>> m_shapes;
	CommandHistory m_commandHistory;
	std::set<IShapeCompositionObserver*> m_observers;
};

} // namespace model
