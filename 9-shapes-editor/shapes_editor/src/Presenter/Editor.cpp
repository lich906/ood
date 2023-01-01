#include "../../include/Presenter/Editor.h"

Editor::Editor(const std::shared_ptr<IShapeComposition>& shapeComposition, Selection& selection)
	: m_shapeComposition(shapeComposition)
	, m_selection(selection)
{
}

void Editor::ResizeShape(ResizeNode node, float dx, float dy)
{
	if (m_selection)
	{
		auto shape = m_shapeComposition->GetShapeById(m_selection.GetSelectedShape()->GetId());
		
		switch (node)
		{
		case ResizeNode::None:
			throw std::invalid_argument("Failed to resize shape: resize node is None value");
		case ResizeNode::TopLeft:
		{
			auto tl = shape->GetTopLeft();
			shape->Resize({ tl.x + dx, tl.y + dy }, shape->GetBottomRight());
		}
		break;
		case ResizeNode::TopRight:
		{
			auto tl = shape->GetTopLeft();
			auto br = shape->GetBottomRight();
			shape->Resize({ tl.x, tl.y + dy }, { br.x + dx, br.y });
		}
		break;
		case ResizeNode::BottomRight:
		{
			auto br = shape->GetTopLeft();
			shape->Resize(shape->GetTopLeft(), { br.x + dx, br.y + dy });
		}
		break;
		case ResizeNode::BottomLeft:
		{
			auto tl = shape->GetTopLeft();
			auto br = shape->GetBottomRight();
			shape->Resize({ tl.x + dx, tl.y }, { br.x, br.y + dy });
		}
		break;
		default:
			throw std::invalid_argument("Failed to resize shape: unsupported value of resize node");
		}
	}
}

void Editor::MoveShape(float dx, float dy)
{
	if (m_selection)
	{
		auto shape = m_shapeComposition->GetShapeById(m_selection.GetSelectedShape()->GetId());
		shape->Move(dx, dy);
	}
}

void Editor::CreateShape(ShapeType type)
{
	m_shapeComposition->AddShape(type);
}

void Editor::DeleteShape()
{
	if (m_selection)
	{
		m_shapeComposition->RemoveShape(m_selection.GetSelectedShape()->GetId());
		m_selection.Reset();
	}
}

void Editor::ChangeFillColor(const Color& color)
{
	if (m_selection)
	{
		auto shape = m_shapeComposition->GetShapeById(m_selection.GetSelectedShape()->GetId());
		shape->SetFillColor(color);
	}
}

void Editor::ChangeBorderColor(const Color& color)
{
	if (m_selection)
	{
		auto shape = m_shapeComposition->GetShapeById(m_selection.GetSelectedShape()->GetId());
		shape->SetBorderColor(color);
	}
}

void Editor::Undo()
{
	m_shapeComposition->Undo();
}

void Editor::Redo()
{
	m_shapeComposition->Redo();
}
