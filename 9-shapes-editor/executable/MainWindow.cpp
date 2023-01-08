#include "MainWindow.h"

void app::MainWindow::Init(view::IShapePresenter* shapePresenter)
{
	m_shapePresenter = shapePresenter;
}

void app::MainWindow::Run()
{
	CanvasArea();
	HandleKeyboardInput();

	if (m_shapePresenter->IsShapeSelected())
	{
		SelectedShapeWindow();
	}
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
	if (data.id != m_selectedShapeData.id)
	{
		m_curFillColor = utils::ColorToImVec4(data.fillColor);
		m_curBorderColor = utils::ColorToImVec4(data.borderColor);
	}

	m_selectedShapeData = data;
}

void app::MainWindow::CanvasArea()
{
	ImGui::Begin("Canvas area", NULL, ImGuiWindowFlags_MenuBar);

	MenuBar();

	ImVec2 origin = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
	m_canvasOrigin = origin;
	ImVec2 canvasSize = ImVec2(
		((view::ICanvas*)&m_canvas)->GetWidth(),
		((view::ICanvas*)&m_canvas)->GetHeight()
	);
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
		if (ImGui::BeginMenu("Add shape"))
		{
			if (ImGui::MenuItem("Triangle", "Ctrl + N + T"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Triangle);
			}
			if (ImGui::MenuItem("Rectangle", "Ctrl + N + R"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Rectangle);
			}
			if (ImGui::MenuItem("Ellipse", "Ctrl + N + E"))
			{
				m_shapePresenter->CreateShape(model::ShapeType::Ellipse);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl + Z", false, m_shapePresenter->CanUndo()))
			{
				m_shapePresenter->Undo();
			}
			if (ImGui::MenuItem("Redo", "Ctrl + Y", false, m_shapePresenter->CanRedo()))
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

	ImGui::ColorEdit4("Fill color", &m_curFillColor.x, ImGuiColorEditFlags_NoInputs);
	ImGui::SameLine();
	ImGui::ColorEdit4("Border color", &m_curBorderColor.x, ImGuiColorEditFlags_NoInputs);

	if (ImGui::Button("Remove shape (Del)")) m_shapePresenter->DeleteShape();

	if (IsColorChanged() && ImGui::Button("Apply color changes"))
	{
		m_shapePresenter->ChangeFillColor(utils::ImVec4ToColor(m_curFillColor));
		m_shapePresenter->ChangeBorderColor(utils::ImVec4ToColor(m_curBorderColor));
	}

	ImGui::End();
}

void app::MainWindow::HandleKeyboardInput()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Delete))
		m_shapePresenter->DeleteShape(); // Del
	else if (ImGui::IsKeyDown(ImGuiMod_Ctrl))
		if (ImGui::IsKeyPressed(ImGuiKey_Z))
			m_shapePresenter->Undo(); // Ctrl + Z
		else if (ImGui::IsKeyPressed(ImGuiKey_Y))
			m_shapePresenter->Redo(); // Ctrl + Y
		else if (ImGui::IsKeyDown(ImGuiKey_N))
			if (ImGui::IsKeyPressed(ImGuiKey_E))
				m_shapePresenter->CreateShape(model::ShapeType::Ellipse); // Ctrl + N + E
			else if (ImGui::IsKeyPressed(ImGuiKey_T))
				m_shapePresenter->CreateShape(model::ShapeType::Triangle); // Ctrl + N + T
			else if (ImGui::IsKeyPressed(ImGuiKey_R))
				m_shapePresenter->CreateShape(model::ShapeType::Rectangle); // Ctrl + N + R
}

bool app::MainWindow::IsColorChanged() const
{
	return 
		m_selectedShapeData.borderColor != utils::ImVec4ToColor(m_curBorderColor) ||
		m_selectedShapeData.fillColor != utils::ImVec4ToColor(m_curFillColor);
}
