#pragma once

#include "ICanvas.h"
#include "SelectedShapeData.h"

namespace view
{

struct IView
{
	virtual ~IView() = default;

	virtual ICanvas* GetCanvas() = 0;
	virtual common::Point GetMousePos() const = 0;
	virtual common::Point GetMouseDelta() const = 0;
	virtual void SetSelectedShapeData(const SelectedShapeData&) = 0;
};

} // namespace view
