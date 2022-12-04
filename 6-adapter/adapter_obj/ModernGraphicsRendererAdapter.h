#pragma once

#include "graphics_lib.hpp"
#include "modern_graphics_lib.hpp"

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer);

	void MoveTo(int x, int y) override;

	void LineTo(int x, int y) override;

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_currentPoint;
};
