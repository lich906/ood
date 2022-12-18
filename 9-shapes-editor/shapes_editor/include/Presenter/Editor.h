#pragma once

#include "../Model/ShapeStore.h"
#include "CommandHistory.h"

class Editor
{
public:
	Editor(ShapeStore& shapeStore);

	bool IsShapeSelected() const;

private:
	std::optional<size_t> m_selectedShapeId;
	ShapeStore& m_shapeStore;
	CommandHistory m_commandHistory;
};
