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
common::Color ImVec4ToColor(const ImVec4&);
ImVec4 ColorToImVec4(const common::Color&);

} // namespace app::utils
