#pragma once

#include "Common/Color.h"
#include "Common/Point.h"

namespace view
{

struct SelectedShapeData
{
	common::Point topLeft, bottomRight;
	common::Color fillColor, borderColor;
};

} // namespace view
