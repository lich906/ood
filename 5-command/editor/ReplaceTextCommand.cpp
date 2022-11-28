#include "ReplaceTextCommand.h"

ReplaceTextCommand::ReplaceTextCommand(std::string& textRef, const std::string& oldText, const std::string& text)
	: Command(nullptr)
	, m_textRef(textRef)
	, m_text(text)
	, m_oldText(oldText)
{
}

void ReplaceTextCommand::ExecuteImpl()
{
	ReplaceText(m_text);
}

void ReplaceTextCommand::UnexecuteImpl()
{
	ReplaceText(m_oldText);
}

void ReplaceTextCommand::ReplaceText(const std::string& text) const
{
	m_textRef = text;
}


