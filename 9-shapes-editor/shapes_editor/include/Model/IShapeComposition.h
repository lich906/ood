#pragma once

#include <memory>

#include "IShape.h"

struct IShapeComposition
{
	virtual ~IShapeComposition() = default;

	virtual std::shared_ptr<IShape> GetShapeById(ShapeId id) = 0;
	virtual std::shared_ptr<const IShape> GetShapeById(ShapeId id) const = 0;

	/*
	* @return shared_ptr to Shape or nullptr if shape not found
	*/
	virtual std::shared_ptr<IShape> FindShapeByCoords(float x, float y) = 0;

	/*
	* @return shared_ptr to Shape or nullptr if shape not found
	*/
	virtual std::shared_ptr<const IShape> FindShapeByCoords(float x, float y) const = 0;

	virtual void LiftShapeOnTop(ShapeId id) = 0;

	virtual ShapeId AddShape(ShapeType type) = 0;

	virtual void RemoveShape(ShapeId id) = 0;

	virtual void Undo() = 0;

	virtual void Redo() = 0;
};
