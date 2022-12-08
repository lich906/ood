#include "ModernGraphicsRendererAdapter.h"

const modern_graphics_lib::CPoint defaultPoint(0, 0);

ModernGraphicsRendererAdapter::ModernGraphicsRendererAdapter(std::ostream& stream)
	: CModernGraphicsRenderer(stream)
	, m_currentPoint(defaultPoint)
{
	BeginDraw();
}

ModernGraphicsRendererAdapter::~ModernGraphicsRendererAdapter()
{
	EndDraw();
}

void ModernGraphicsRendererAdapter::MoveTo(int x, int y)
{
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}

void ModernGraphicsRendererAdapter::LineTo(int x, int y)
{
	// вызывать BeginDraw() и EndDraw() в конструкторе / деструкторе
	DrawLine(m_currentPoint, { x, y });
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}
