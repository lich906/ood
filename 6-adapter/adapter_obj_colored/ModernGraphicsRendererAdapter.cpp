#include "ModernGraphicsRendererAdapter.h"

const modern_graphics_lib::CPoint defaultPoint(0, 0);
const modern_graphics_lib::CRGBAColor defaultColor(0, 0, 0, 1.0f);

ModernGraphicsRendererAdapter::ModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
	: m_renderer(renderer)
	, m_currentPoint(defaultPoint)
	, m_color(defaultColor)
{
}

void ModernGraphicsRendererAdapter::SetColor(uint32_t rgbColor)
{
	m_color.r = float((rgbColor >> 16) & 0xFF) / 0xFF;
	m_color.g = float((rgbColor >> 8) & 0xFF) / 0xFF;
	m_color.b = float(rgbColor & 0xFF) / 0xFF;
}

void ModernGraphicsRendererAdapter::MoveTo(int x, int y)
{
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}

void ModernGraphicsRendererAdapter::LineTo(int x, int y)
{
	m_renderer.BeginDraw();
	m_renderer.DrawLine(m_currentPoint, { x, y }, m_color);
	m_renderer.EndDraw();
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}
