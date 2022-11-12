#ifndef I_PAINTER_H
#define I_PAINTER_H

#include "PictureDraft.h"

class IPainter
{
public:
	virtual ~IPainter() = default;

	virtual void DrawPicture(const PictureDraft& draft, ICanvas* canvas) const = 0;
};

#endif // !I_PAINTER_H
