#pragma once

#include <memory>

#include "IShape.h"
#include "IShapeCompositionObserver.h"

namespace model
{

struct IShapeComposition
{
	virtual ~IShapeComposition() = default;

	virtual ShapePtr GetShapeById(ShapeId id) = 0;

	virtual ShapePtr GetSelectedShape() = 0;

	virtual void SelectShapeAtCoords(float x, float y) = 0;

	virtual ShapeId AddShape(ShapeType type) = 0;
	virtual void RemoveSelectedShape() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;

	virtual void RegisterOnChange(IShapeCompositionObserver* observer) = 0;
};

} // namespace model
