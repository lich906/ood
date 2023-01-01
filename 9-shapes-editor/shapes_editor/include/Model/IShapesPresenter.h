#pragma once

#include <vector>
#include <memory>

#include "Shape.h"

struct IShapesPresenter
{
	virtual ~IShapesPresenter() = default;
	virtual void UpdatePresentation(const std::vector<std::shared_ptr<Shape>>& shapes) = 0;
};
