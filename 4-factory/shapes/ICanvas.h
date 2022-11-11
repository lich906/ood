#ifndef I_CANVAS_H
#define I_CANVAS_H

#include <memory>

#include "Point.hpp"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Point center, size_t width, size_t height) = 0;
};

typedef std::unique_ptr<ICanvas> CanvasPtr;

#endif // !I_CANVAS_H
