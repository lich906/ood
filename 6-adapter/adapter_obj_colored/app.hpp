#pragma once

#include "shape_drawing_lib.hpp"
#include "modern_graphics_lib.hpp"
#include "ModernGraphicsRendererAdapter.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xFF00FF);
	CRectangle rectangle({ 30, 40 }, 18, 24, 0xFFFF00);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
	ModernGraphicsRendererAdapter adapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(adapter);
	PaintPicture(painter);
}
} // namespace app
