#pragma once

#include <vector>
#include <memory>

#include "IShape.h"

namespace model
{

struct IShapeCompositionObserver
{
	virtual ~IShapeCompositionObserver() = default;

	virtual void OnChange(const std::vector<ShapePtr>& shapes) = 0;
};

} // namespace model
