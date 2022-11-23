#include "Paragraph.h"

Paragraph::Paragraph(std::string text)
	: m_text(std::move(text))
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	m_text = text;
}
