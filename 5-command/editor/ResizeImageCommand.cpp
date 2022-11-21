#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(const std::shared_ptr<IDocumentEditContext>& document, size_t index,
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

void ResizeImageCommand::ResizeImage(int width, int height) const
{
	if (auto image = m_documentEditContext->GetItemForEdit(m_index).GetImage())
	{
		if (width < MIN_DIMENSION_SIZE || width > MAX_DIMENSION_SIZE || height < MIN_DIMENSION_SIZE || height > MAX_DIMENSION_SIZE)
		{
			throw CommandExecutionException("Unable to resize image: unacceptable size");
		}

		image->Resize(m_width, m_height);
	}
	else
	{
		throw CommandExecutionException("Unable to resize image: item at position isn't an image");
	}
}
