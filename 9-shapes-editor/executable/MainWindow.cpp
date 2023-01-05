#include "MainWindow.h"

void app::MainWindow::Init(view::IShapePresenter* shapePresenter)
{
	m_shapePresenter = shapePresenter;
}

void app::MainWindow::Run()
{
	CanvasArea();
	MainMenu();
}

view::ICanvas* app::MainWindow::GetCanvas()
{
	return &m_canvas;
}

common::Point app::MainWindow::GetMousePos() const
{
	ImGuiIO& io = ImGui::GetIO();
	return { io.MousePos.x - m_canvasOrigin.x, io.MousePos.y - m_canvasOrigin.y };
}

common::Point app::MainWindow::GetMouseDelta() const
{
	ImGuiIO& io = ImGui::GetIO();
	return { io.MouseDelta.x, io.MouseDelta.y };
}

void app::MainWindow::CanvasArea()
{
	ImGui::Begin("Canvas area");

	ImVec2 origin = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
	m_canvasOrigin = origin;
	ImVec2 canvasSize = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
	if (canvasSize.x < 50.0f)
		canvasSize.x = 50.0f;
	if (canvasSize.y < 50.0f)
		canvasSize.y = 50.0f;
	ImVec2 canvasBtmRight = ImVec2(origin.x + canvasSize.x, origin.y + canvasSize.y);

	// Draw border and background color
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(origin, canvasBtmRight, constants::CanvasClearColor);
	drawList->AddRect(origin, canvasBtmRight, IM_COL32(255, 255, 255, 255));

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool isHovered = ImGui::IsItemHovered(); // Hovered
	const bool isActive = ImGui::IsItemActive(); // Held

	if (!m_mouseDown && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && isActive)
	{
		m_shapePresenter->OnMouseDown();
		m_mouseDown = true;
	}

	if (m_mouseDown && !ImGui::IsMouseDown(ImGuiMouseButton_Left) && isHovered)
	{
		m_shapePresenter->OnMouseUp();
		m_mouseDown = false;
	}

	if (isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_shapePresenter->OnMouseDrag();
	}

	drawList->PushClipRect(origin, canvasBtmRight, true);
	m_canvas.SetOrigin(origin);
	m_canvas.SetImDrawList(drawList);
	m_canvas.Draw();
	drawList->PopClipRect();

	ImGui::End();
}

void app::MainWindow::MainMenu()
{
	ImGui::Begin("Main menu", NULL, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
			}
			if (ImGui::MenuItem("Save As"))
			{
			}
			if (ImGui::MenuItem("Close"))
			{
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("New"))
		{
			if (ImGui::MenuItem("Triangle"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Triangle);
			}
			if (ImGui::MenuItem("Rectangle"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Rectangle);
			}
			if (ImGui::MenuItem("Ellipse"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Ellipse);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				m_shapePresenter->Undo();
			}
			if (ImGui::MenuItem("Redo"))
			{
				m_shapePresenter->Redo();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	ImGui::End();
}
