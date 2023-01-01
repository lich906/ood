#pragma once

#include "Presenter/Selection.h"
#include "ResizeNode.h"
#include "IMouseActionsHandler.h"
#include "IMenuActionsHandler.h"
#include "../Model/ShapeComposition.h"
#include "Command/CommandHistory.h"
#include "Command/FunctionalCommand.h"
#include "constants.h"

class Editor : public IMenuActionsHandler
{
public:
	Editor(const std::shared_ptr<IShapeComposition>& shapeComposition, Selection& selection);

	void CreateShape(ShapeType type) override;
	void DeleteShape() override;
	void ChangeFillColor(const Color& color) override;
	void ChangeBorderColor(const Color& color) override;
	void Undo() override;
	void Redo() override;

private:
	void ResizeShape(ResizeNode node, float dx, float dy);
	void MoveShape(float dx, float dy);

	ResizeNode m_resizeNode = ResizeNode::None;
	Selection& m_selection;
	std::shared_ptr<IShapeComposition> m_shapeComposition;
};
