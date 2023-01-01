#pragma once

#include <memory>

#include "Model/Shape.h"

class Selection
{
public:
	void SetSelectedShape(const std::shared_ptr<const Shape>& shape);
	std::shared_ptr<const Shape> GetSelectedShape();
	void Reset();

	operator bool() const;

private:
	std::shared_ptr<const Shape> m_selectedShape;
};
