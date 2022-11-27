#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(IDocumentEditContext* document, size_t index,
	int width, int height, int oldWidth, int oldHeight)
	: Command(document)
	, m_index(index)
	, m_width(width), m_height(height)
	, m_oldWidth(oldWidth), m_oldHeight(oldHeight)
{
}

void ResizeImageCommand::ExecuteImpl()
{
	ResizeImage(m_width, m_height);
}

void ResizeImageCommand::UnexecuteImpl()
{
	ResizeImage(m_oldWidth, m_oldHeight);
}

void ResizeImageCommand::ResizeImage(int w, int h) const
{
	if (auto image = m_documentEditContext->GetItemForEdit(m_index).GetImage())
	{
		image->Resize(w, h);
	}
	else
	{
		throw CommandExecutionException("Unable to resize image: item at position isn't an image");
	}
}