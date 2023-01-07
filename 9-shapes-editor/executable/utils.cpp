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

common::Color app::utils::ImVec4ToColor(const ImVec4& col)
{
	return {
		static_cast<uint8_t>(col.x * 0xFF),
		static_cast<uint8_t>(col.y * 0xFF),
		static_cast<uint8_t>(col.z * 0xFF),
		static_cast<uint8_t>(col.w * 0xFF)
	};
}

ImVec4 app::utils::ColorToImVec4(const common::Color& col)
{
	return ImVec4(
		static_cast<float>(col.r / 255.0f),
		static_cast<float>(col.g / 255.0f),
		static_cast<float>(col.b / 255.0f),
		static_cast<float>(col.a / 255.0f)
	);
}
