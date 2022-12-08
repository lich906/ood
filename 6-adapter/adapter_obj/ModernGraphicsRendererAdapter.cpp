#include "ModernGraphicsRendererAdapter.h"

const modern_graphics_lib::CPoint defaultPoint(0, 0);

ModernGraphicsRendererAdapter::ModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
	: m_renderer(renderer)
	, m_currentPoint(defaultPoint)
{
}

void ModernGraphicsRendererAdapter::MoveTo(int x, int y)
{
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}

void ModernGraphicsRendererAdapter::LineTo(int x, int y)
{
	// не вызывать BeginDraw(), EndDraw()
	m_renderer.DrawLine(m_currentPoint, { x, y });
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}
