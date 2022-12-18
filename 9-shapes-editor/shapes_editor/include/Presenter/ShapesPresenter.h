#pragma once

#include <optional>

#include "../Model/ShapeStore.h"
#include "ResizeNode.h"
#include "../View/ICanvas.h"
#include "IMouseActionsHandler.h"

namespace constants
{
constexpr auto ResizeMarkerSize = 10;
}

class ShapesPresenter : public IMouseActionsHandler
{
public:
	ShapesPresenter(ShapeStore& shapeStore);

	void UpdateView(ICanvasPtr canvas);

	bool IsResizing() const;

	void OnMouseDown(float x, float y) override;

	void OnMouseUp(float dx, float dy) override;

	void OnMouseDrag(float dx, float dy) override;

	void StopResizing();

	void ResetSelection();

private:
	void UpdateSelectedShape(float x, float y);

	std::optional<ResizeNode> GetPressedResizeNode(float x, float y) const;

	std::optional<size_t> m_selectedShapeId;
	ShapeStore& m_shapeStore;
	ResizeNode m_currentResizeNode = ResizeNode::None;
};
