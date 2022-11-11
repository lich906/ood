#include "PictureDraft.h"

size_t PictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

const ShapePtr& PictureDraft::GetShape(size_t index) const
{
	return m_shapes.at(index);
}

PictureDraft& PictureDraft::AddShape(ShapePtr&& shape)
{
	m_shapes.emplace_back(std::forward<ShapePtr>(shape));

	return *this;
}
