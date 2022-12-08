#pragma once

#include "graphics_lib.hpp"
#include "modern_graphics_lib.hpp"

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsRendererAdapter(std::ostream& stream);

	~ModernGraphicsRendererAdapter();

	void MoveTo(int x, int y) override;

	void LineTo(int x, int y) override;

private:
	modern_graphics_lib::CPoint m_currentPoint;
};
