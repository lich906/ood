#include "Presenter/Selection.h"

void Selection::SetSelectedShape(const std::shared_ptr<const Shape>& shape)
{
	m_selectedShape = shape;
}

std::shared_ptr<const Shape> Selection::GetSelectedShape()
{
	return m_selectedShape;
}

void Selection::Reset()
{
	m_selectedShape.reset();
}

Selection::operator bool() const
{
	return (bool)m_selectedShape;
}
