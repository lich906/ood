#pragma once

#include "Point.h"
#include "Color.h"

namespace Defaults
{
constexpr Point TopLeftPoint = { 0, 0 };
constexpr Point BottomRightPoint = { 70, 70 };
constexpr Color FillColor = { 1.0f, 0.0f, 0.0f, 1.0f };
constexpr Color BorderColor = { 1.0f, 1.0f, 0.0f, 1.0f };
} // namespace Defaults
