#pragma once

#include "../Model/ShapeType.h"
#include "../Model/Color.h"

struct IMenuActionsHandler
{
	virtual ~IMenuActionsHandler() = default;
	virtual void CreateShape(ShapeType type) = 0;
	virtual void DeleteShape() = 0;
	virtual void ChangeFillColor(const Color& color) = 0;
	virtual void ChangeBorderColor(const Color& color) = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};
