#pragma once

#include "View/IShapePresenter.h"
#include "View/IView.h"
#include "ImCanvas.h"

namespace app
{

class MainWindow : public view::IView
{
public:
	void Init(view::IShapePresenter* shapePresenter);

	void Run();

private:
	// <<interface>> IView
	view::ICanvas* GetCanvas() override;
	common::Point GetMousePos() const override;
	common::Point GetMouseDelta() const override;
	void SetSelectedShapeData(const view::SelectedShapeData&) override;
	// >>>>>>>>>>>>>>>>>>>

	void CanvasArea();
	void MenuBar();
	void SelectedShapeWindow();
	void HandleKeyboardInput();
	bool IsColorChanged() const;

	view::SelectedShapeData m_selectedShapeData;
	ImVec2 m_canvasOrigin;
	ImCanvas m_canvas;
	view::IShapePresenter* m_shapePresenter = nullptr;
	bool m_isMouseDown = false;
	ImVec4 m_curFillColor;
	ImVec4 m_curBorderColor;
};

} // namespace app
