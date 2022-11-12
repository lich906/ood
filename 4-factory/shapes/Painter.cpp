#include "Painter.h"

void Painter::DrawPicture(const PictureDraft& draft, ICanvas* canvas) const
{
	for (size_t index = 0; index < draft.GetShapeCount(); ++index)
	{
		draft.GetShape(index)->Draw(canvas);
	}
}
