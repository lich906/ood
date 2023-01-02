#pragma once

#include <vector>
#include <memory>

#include "Shape.h"

struct IShapePresenter
{
	virtual ~IShapePresenter() = default;
	virtual void UpdatePresentation(const std::vector<std::shared_ptr<Shape>>& shapes) = 0;
};
