#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <functional>

#include "utils.h"
#include "constants.h"
#include "View/ICanvas.h"

namespace app
{

class ImCanvas : public view::ICanvas
{
public:
	ImCanvas() = default;
	ImCanvas(float width, float height);

	void SetImDrawList(ImDrawList* drawList);
	void SetOrigin(ImVec2 origin);
	void Draw();

private:
	// <<interface>> ICanvas
	void FillPolygon(const std::vector<common::Point>& points, const common::Color& color) override;
	void DrawOutline(const std::vector<common::Point>& points, const common::Color& color) override;
	void DrawEllipse(common::Point topLeft, common::Point bottomRight, const common::Color& fillColor, const common::Color& borderColor) override;
	void Clear() override;
	float GetWidth() const override;
	float GetHeight() const override;
	// >>>>>>>>>>>>>>>>>>>>>

	std::vector<ImVec2> TranslatePointsToCanvasOrigin(const std::vector<ImVec2>&) const;

	// Container that stores all draw command that should be executed on each render
	std::vector<std::function<void()>> m_drawQ;

	ImVec2 m_origin;
	ImDrawList* m_drawList = nullptr;
	float m_width = constants::CanvasWidth, m_height = constants::CanvasHeight;
};

} // namespace app
