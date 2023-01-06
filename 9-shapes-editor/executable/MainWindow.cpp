#include "MainWindow.h"

void app::MainWindow::Init(view::IShapePresenter* shapePresenter)
{
	m_shapePresenter = shapePresenter;
}

void app::MainWindow::Run()
{
	CanvasArea();
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

void app::MainWindow::SetSelectedShapeData(const view::SelectedShapeData& data)
{
	m_selectedShapeData = data;
}

void app::MainWindow::CanvasArea()
{
	ImGui::Begin("Canvas area", NULL, ImGuiWindowFlags_MenuBar);

	MenuBar();

	if (m_shapePresenter->IsShapeSelected())
		SelectedShapeWindow();

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

	if (!m_isMouseDown && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && isActive)
	{
		m_shapePresenter->OnMouseDown();
		m_isMouseDown = true;
	}

	if (m_isMouseDown && !ImGui::IsMouseDown(ImGuiMouseButton_Left) && isHovered)
	{
		m_shapePresenter->OnMouseUp();
		m_isMouseDown = false;
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

void app::MainWindow::MenuBar()
{
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

		if (ImGui::BeginMenu("Add shape"))
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
			if (ImGui::MenuItem("Undo", NULL, false, m_shapePresenter->CanUndo()))
			{
				m_shapePresenter->Undo();
			}
			if (ImGui::MenuItem("Redo", NULL, false, m_shapePresenter->CanRedo()))
			{
				m_shapePresenter->Redo();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void app::MainWindow::SelectedShapeWindow()
{
	ImGui::Begin("Selected shape");

	if (ImGui::BeginTable("Boundings", 2))
	{
// clang-format off
		ImGui::TableNextRow(); ImGui::TableSetColumnIndex(0); ImGui::Text("Top left:"); ImGui::TableSetColumnIndex(1); ImGui::Text("Bottom right:");
		ImGui::TableNextRow(); ImGui::TableSetColumnIndex(0); ImGui::Text("x: %.1f", m_selectedShapeData.topLeft.x); ImGui::TableSetColumnIndex(1); ImGui::Text("x: %.1f", m_selectedShapeData.bottomRight.x);
		ImGui::TableNextRow(); ImGui::TableSetColumnIndex(0); ImGui::Text("y: %.1f", m_selectedShapeData.topLeft.y); ImGui::TableSetColumnIndex(1); ImGui::Text("y: %.1f", m_selectedShapeData.bottomRight.y);
		
		ImGui::EndTable();
// clang-format on
	}
	static bool isColorChanged = false;
	static float curFillColor[4];
	static float curBorColor[4];
	if(ImGui::ColorEdit4("Fill color", curFillColor, ImGuiColorEditFlags_NoInputs)) isColorChanged = true;
	ImGui::SameLine();
	if(ImGui::ColorEdit4("Border color", curBorColor, ImGuiColorEditFlags_NoInputs)) isColorChanged = true;

	if (ImGui::Button("Remove shape")) m_shapePresenter->DeleteShape();
	ImGui::SameLine();
	if (isColorChanged && ImGui::Button("Apply color changes"))
	{
		m_shapePresenter->ChangeFillColor(utils::ImVec4ToColor(curFillColor));
		m_shapePresenter->ChangeBorderColor(utils::ImVec4ToColor(curBorColor));
		isColorChanged = false;
	}

	ImGui::End();
}
