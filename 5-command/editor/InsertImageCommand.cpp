#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(IDocumentEditContext* document, const std::shared_ptr<IImage>& image, std::optional<size_t> position)
	: Command(document)
	, m_image(image)
	, m_index(position)
{
}

void InsertImageCommand::ExecuteImpl()
{
	m_documentEditContext->InsertImageEdit(m_image, m_index);
}

void InsertImageCommand::UnexecuteImpl()
{
	if (m_index.has_value())
	{
		m_documentEditContext->DeleteItemEdit(*m_index);
	}
	else
	{
		m_documentEditContext->DeleteLastItemEdit();
	}
}
