#ifndef PAINTER_H
#define PAINTER_H

#include "IPainter.h"

class Painter : public IPainter
{
public:
	void DrawPicture(const PictureDraft& draft, CanvasPtr& canvas) const override;
};

#endif // !PAINTER_H
