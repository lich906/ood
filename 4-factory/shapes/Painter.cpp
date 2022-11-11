#include "Painter.h"

void Painter::DrawPicture(const PictureDraft& draft, CanvasPtr& canvas) const
{
	for (size_t index = 0; index < draft.GetShapeCount(); ++index)
	{
		draft.GetShape(index)->Draw(canvas);
	}
}
