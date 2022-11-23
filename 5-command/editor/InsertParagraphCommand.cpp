#include "InsertParagraphCommand.h"

InsertParagraphCommand::InsertParagraphCommand(IDocumentEditContext* document,
	const std::shared_ptr<IParagraph>& paragraph, std::optional<size_t> position)
	: Command(document)
	, m_paragraph(paragraph)
	, m_index(std::move(position))
{
}

void InsertParagraphCommand::ExecuteImpl()
{
	m_documentEditContext->InsertParagraphEdit(m_paragraph, m_index);
}

void InsertParagraphCommand::UnexecuteImpl()
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
