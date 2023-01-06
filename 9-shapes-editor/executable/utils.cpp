#include "utils.h"

std::vector<ImVec2> app::utils::ToImVec2Vector(const std::vector<common::Point>& v)
{
	std::vector<ImVec2> res;
	std::for_each(v.begin(), v.end(), [&](const common::Point& p) {
		res.emplace_back(ImVec2(p.x, p.y));
	});

	return res;
}

ImU32 app::utils::ToImU32(const common::Color& col)
{
	return IM_COL32(col.r, col.g, col.b, col.a);
}

common::Color app::utils::ImVec4ToColor(float col[4])
{
	return {
		static_cast<uint8_t>(col[0] * 0xFF),
		static_cast<uint8_t>(col[1] * 0xFF),
		static_cast<uint8_t>(col[2] * 0xFF),
		static_cast<uint8_t>(col[3] * 0xFF)
	};
}
