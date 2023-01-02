#pragma once

#include <optional>

#include "Selection.h"
#include "../Model/IShapesPresenter.h"
#include "../Model/ShapeComposition.h"
#include "ResizeNode.h"
#include "../View/ICanvas.h"
#include "IMouseActionsHandler.h"
#include "constants.h"

class ShapePresenter : public IShapePresenter, public IMouseActionsHandler
{
public:
	ShapePresenter(const ShapeComposition& shapeStore, Selection& selection);

	void UpdatePresentation(const std::vector<std::shared_ptr<Shape>>& shapes);

	void OnMouseDown(float x, float y) override;

	void OnMouseUp(float dx, float dy) override;

	void OnMouseDrag(float dx, float dy) override;

private:
	void UpdateShapeSelection(float x, float y);
	ResizeNode GetPressedResizeNode(float x, float y) const;
	void DrawShape(const Shape& shape, ICanvasPtr canvas);
	void DrawSelectionFrame(const Point& leftTop, const Point& bottomRight, ICanvasPtr canvas);

	Selection& m_selection;
	const ShapeComposition& m_shapeComposition;
	ResizeNode m_resizeNode = ResizeNode::None;
	bool m_isMoving = false;

	Point m_dragOffset;
};
