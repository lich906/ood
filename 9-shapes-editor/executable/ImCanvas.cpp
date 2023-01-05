#include "ImCanvas.h"

app::ImCanvas::ImCanvas(float width, float height)
	: m_width(width)
	, m_height(height)
{
}

void app::ImCanvas::SetImDrawList(ImDrawList* drawList)
{
	m_drawList = drawList;
}

void app::ImCanvas::SetOrigin(ImVec2 origin)
{
	m_origin = origin;
}

void app::ImCanvas::Draw()
{
	std::for_each(m_drawQ.begin(), m_drawQ.end(),
		[](const std::function<void()>& fn) { fn(); });
}

void app::ImCanvas::Clear()
{
	m_drawQ.clear();
}

void app::ImCanvas::FillPolygon(const std::vector<common::Point>& points, const common::Color& color)
{
	if (m_drawList)
	{
		m_drawQ.emplace_back([this, points = ToImVector(points), col = ToImU32(color)]() {
			auto translatedPoints = TranslatePointsToCanvasOrigin(points);
			m_drawList->AddConvexPolyFilled(translatedPoints.data(), translatedPoints.size(), col);
		});
	}
}

void app::ImCanvas::DrawOutline(const std::vector<common::Point>& points, const common::Color& color)
{
	if (m_drawList)
	{
		m_drawQ.emplace_back([this, points = ToImVector(points), col = ToImU32(color)]() {
			auto translatedPoints = TranslatePointsToCanvasOrigin(points);
			m_drawList->AddPolyline(translatedPoints.data(), translatedPoints.size(),
				col, ImDrawFlags_Closed, constants::OutlineThickness);
		});
	}
}

void app::ImCanvas::DrawEllipse(common::Point topLeft, common::Point bottomRight, const common::Color& fillColor, const common::Color& borderColor)
{
	if (m_drawList)
	{
		static const float doublePi = 2.0f * M_PI;
		const float
			cx = (topLeft.x + bottomRight.x) / 2,
			cy = (topLeft.y + bottomRight.y) / 2,
			w = (bottomRight.x - topLeft.x) / 2,
			h = (bottomRight.y - topLeft.y) / 2;
		std::vector<ImVec2> points;
		int pointsNum = m_drawList->_CalcCircleAutoSegmentCount(std::max(w, h));
		for (float a = 0.0f; a <= doublePi; a += (doublePi / pointsNum))
		{
			const float x = cx + cos(a) * w;
			const float y = cy + sin(a) * h;
			points.push_back(ImVec2(x, y));
		}
		m_drawQ.emplace_back([this, points, fillCol = ToImU32(fillColor), borCol = ToImU32(borderColor)]() {
			auto translatedPoints = TranslatePointsToCanvasOrigin(points);
			m_drawList->AddConvexPolyFilled(translatedPoints.data(), translatedPoints.size(), fillCol);
			m_drawList->AddPolyline(translatedPoints.data(), translatedPoints.size(),
				borCol, ImDrawFlags_Closed, constants::OutlineThickness);
		});
	}
}

float app::ImCanvas::GetWidth()
{
	return m_width;
}

float app::ImCanvas::GetHeight()
{
	return m_height;
}

std::vector<ImVec2> app::ImCanvas::TranslatePointsToCanvasOrigin(const std::vector<ImVec2>& v) const
{
	std::vector<ImVec2> res;
	std::for_each(v.begin(), v.end(), [&](const ImVec2& p) {
		res.emplace_back(ImVec2(m_origin.x + p.x, m_origin.y + p.y));
	});

	return res;
}

std::vector<ImVec2> app::ImCanvas::ToImVector(const std::vector<common::Point>& v)
{
	std::vector<ImVec2> res;
	std::for_each(v.begin(), v.end(), [&](const common::Point& p) {
		res.emplace_back(ImVec2(p.x, p.y));
	});

	return res;
}

ImU32 app::ImCanvas::ToImU32(const common::Color& col)
{
	return IM_COL32(col.r, col.g, col.b, col.a);
}
