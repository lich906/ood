#ifndef PICTURE_DRAFT_H
#define PICTURE_DRAFT_H

#include <vector>

#include "IShape.h"

class PictureDraft
{
public:
	size_t GetShapeCount() const;
	const ShapePtr& GetShape(size_t index) const;

	PictureDraft& AddShape(ShapePtr&& shape);

private:
	std::vector<ShapePtr> m_shapes;
};

#endif // !PICTURE_DRAFT_H
