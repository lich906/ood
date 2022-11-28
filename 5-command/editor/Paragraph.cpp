#include "Paragraph.h"

Paragraph::Paragraph(IDocumentEditContext* const documentEditCtx, size_t index, std::string text)
	: m_documentEditContext(documentEditCtx)
	, m_position(index)
	, m_text(std::move(text))
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	m_documentEditContext->ReplaceParagraphText(m_position, m_text, text);
}
