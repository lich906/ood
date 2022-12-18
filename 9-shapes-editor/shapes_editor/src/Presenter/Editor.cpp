#include "../../include/Presenter/Editor.h"

Editor::Editor(ShapeStore& shapeStore)
	: m_shapeStore(shapeStore)
{
}

bool Editor::IsShapeSelected() const
{
	return false;
}
