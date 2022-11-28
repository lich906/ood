#include "InsertParagraphCommand.h"

InsertParagraphCommand::InsertParagraphCommand(IDocumentEditContext* document,
	const std::shared_ptr<IParagraph>& paragraph, std::optional<size_t> position)
	: Command(document)
	, m_paragraph(paragraph)
	, m_position(std::move(position))
{
}

void InsertParagraphCommand::ExecuteImpl()
{
	m_documentEditContext->InsertParagraphEdit(m_paragraph, m_position);
}

void InsertParagraphCommand::UnexecuteImpl()
{
	if (m_position.has_value())
	{
		m_documentEditContext->DeleteItemEdit(*m_position);
	}
	else
	{
		m_documentEditContext->DeleteLastItemEdit();
	}
}
