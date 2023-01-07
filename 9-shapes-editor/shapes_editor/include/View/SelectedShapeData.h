#pragma once

#include "Model/IShape.h"
#include "Common/Color.h"
#include "Common/Point.h"

namespace view
{

struct SelectedShapeData
{
	model::ShapeId id;
	common::Point topLeft;
	common::Point bottomRight;
	common::Color fillColor;
	common::Color borderColor;
};

} // namespace view
