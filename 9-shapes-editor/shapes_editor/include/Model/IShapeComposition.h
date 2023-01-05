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
	virtual ShapeConstPtr GetShapeById(ShapeId id) const = 0;

	/*
	 * @return shared_ptr to Shape or nullptr if shape not found
	 */
	virtual ShapePtr FindShapeAtCoords(float x, float y) = 0;

	/*
	 * @return shared_ptr to Shape or nullptr if shape not found
	 */
	virtual ShapeConstPtr FindShapeAtCoords(float x, float y) const = 0;

	virtual void RegisterOnChange(IShapeCompositionObserver* observer) = 0;

	virtual void LiftShapeOnTop(ShapeId id) = 0;

	virtual ShapeId AddShape(ShapeType type) = 0;

	virtual void RemoveShape(ShapeId id) = 0;

	virtual void Undo() = 0;

	virtual void Redo() = 0;
};

} // namespace model
