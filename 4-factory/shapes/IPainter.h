#ifndef I_PAINTER_H
#define I_PAINTER_H

#include "PictureDraft.h"

class IPainter
{
public:
	virtual ~IPainter() = default;

	virtual void DrawPicture(const PictureDraft& draft, CanvasPtr& canvas) const = 0;
};

typedef std::unique_ptr<IPainter> PainterPtr;

#endif // !I_PAINTER_H
