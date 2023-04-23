#pragma once

#include <vector>
#include <memory>

#include "IShape.h"

namespace model
{

struct IShapeCompositionObserver
{
	virtual ~IShapeCompositionObserver() = default;

	virtual void OnChange(const std::vector<ShapeConstPtr>& shapes) = 0;
};

} // namespace model
