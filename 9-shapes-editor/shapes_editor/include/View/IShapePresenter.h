#pragma once

#include "Model/ShapeType.h"
#include "Common/Color.h"

namespace view
{

struct IShapePresenter
{
	virtual ~IShapePresenter() = default;

	virtual void OnMouseDown() = 0;
	virtual void OnMouseUp() = 0;
	virtual void OnMouseDrag() = 0;
	virtual void CreateShape(model::ShapeType) = 0;
	virtual void DeleteShape() = 0;
	virtual void ChangeFillColor(const common::Color&) = 0;
	virtual void ChangeBorderColor(const common::Color&) = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;
};

} // namespace view
