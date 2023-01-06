#pragma once

#include <algorithm>
#include <vector>

#include "imgui.h"
#include "Common/Point.h"
#include "Common/Color.h"

namespace app::utils
{

std::vector<ImVec2> ToImVec2Vector(const std::vector<common::Point>&);
ImU32 ToImU32(const common::Color&);
common::Color ImVec4ToColor(float[4]);

} // namespace app::utils
