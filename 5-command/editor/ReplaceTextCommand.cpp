#include "ReplaceTextCommand.h"

ReplaceTextCommand::ReplaceTextCommand(IDocumentEditContext* document, size_t index,
	const std::string& text, const std::string& oldText)
	: Command(document)
	, m_index(index)
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
	if (auto paragraph = m_documentEditContext->GetItemForEdit(m_index).GetParagraph())
	{
		paragraph->SetText(text);
	}
	else
	{
		throw CommandExecutionException("Unable to replace paragraph text: item at index isn't a paragraph");
	}
}


