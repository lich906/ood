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
	// >>>>>>>>>>>>>>>>>>>

	void CanvasArea();
	void MenuBar();

	ImVec2 m_canvasOrigin;
	ImCanvas m_canvas;
	view::IShapePresenter* m_shapePresenter = nullptr;

	bool m_mouseDown = false;
};

} // namespace app
