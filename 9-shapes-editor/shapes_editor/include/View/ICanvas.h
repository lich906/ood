#pragma once

#include <vector>
#include <memory>

#include "Common/Point.h"
#include "Common/Color.h"

namespace view
{

struct ICanvas
{
	virtual ~ICanvas() = default;
	virtual void FillPolygon(const std::vector<common::Point>& points, const common::Color& color) = 0;
	virtual void DrawOutline(const std::vector<common::Point>& points, const common::Color& color) = 0;
	virtual void DrawEllipse(common::Point topLeft, common::Point bottomRight, const common::Color& fillColor, const common::Color& borderColor) = 0;
	virtual void Clear() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
};

} // namespace view
