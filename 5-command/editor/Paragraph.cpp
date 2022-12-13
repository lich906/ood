#include "Paragraph.h"

Paragraph::Paragraph(std::string text, std::function<void(std::unique_ptr<Command>&&)> commandSaver)
	: m_text(std::move(text))
	, m_commandSaver(std::move(commandSaver))
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	std::unique_ptr<Command> command = std::make_unique<ReplaceTextCommand>(
		[this, text]() {
			m_text = text;
		},
		[this, oldText = m_text]() {
			m_text = oldText;
		}
	);

	command->Execute();

	m_commandSaver(std::move(command));
}
