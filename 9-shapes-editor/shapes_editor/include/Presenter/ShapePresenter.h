#pragma once

#include <optional>
#include <stdexcept>

#include "ResizeNode.h"
#include "constants.h"

#include "View/IShapePresenter.h"
#include "View/ICanvas.h"
#include "View/IView.h"

#include "Model/IShapeComposition.h"

namespace presenter
{

class ShapePresenter : public view::IShapePresenter, public model::IShapeCompositionObserver
{
public:
	ShapePresenter(model::IShapeComposition* shapeComposition, view::IView* view);

	// <<interface>> IShapeCompositionObserver
	void OnChange(const std::vector<model::ShapePtr>& shapes) override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	// <<interface>> IShapePresenter
	void OnMouseDown() override;
	void OnMouseUp() override;
	void OnMouseDrag() override;
	void CreateShape(model::ShapeType) override;
	void DeleteShape() override;
	void ChangeFillColor(const common::Color&) override;
	void ChangeBorderColor(const common::Color&) override;
	void Undo() override;
	void Redo() override;
	bool CanUndo() const override;
	bool CanRedo() const override;
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


private:
	void OnShapeResize(float dx, float dy);
	void OnShapeMove(float dx, float dy);

	void UpdateShapeSelection(float x, float y);
	ResizeNode GetPressedResizeNode(float x, float y) const;

	void UpdateView();
	void DrawShape(const common::Point& topLeft, const common::Point& bottomRight, const model::ShapeConstPtr& shape);
	void DrawTriangle(const common::Point& topLeft, const common::Point& bottomRight, const model::ShapeConstPtr& shape);
	void DrawRectangle(const common::Point& topLeft, const common::Point& bottomRight, const model::ShapeConstPtr& shape);
	void DrawEllipse(const common::Point& topLeft, const common::Point& bottomRight, const model::ShapeConstPtr& shape);
	void DrawSelectionFrame(const common::Point& topLeft, const common::Point& bottomRight);

	std::vector<model::ShapePtr> m_shapes;

	view::IView* m_view;

	struct Selection
	{
		model::ShapePtr shape;
		common::Point topLeft;
		common::Point bottomRight;
	} m_selection;

	model::IShapeComposition* m_shapeComposition;
	ResizeNode m_resizeNode = ResizeNode::None;
	bool m_isMoving = false;
};

} // namespace presenter
