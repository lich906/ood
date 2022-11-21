#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(const std::shared_ptr<IDocumentEditContext>& document, const std::string& title, const std::string& oldTitle)
	: Command(document)
	, m_title(title)
	, m_oldTitle(oldTitle)
{
}

void SetTitleCommand::ExecuteImpl()
{
	m_documentEditContext->SetTitleEdit(m_title);
}

void SetTitleCommand::UnexecuteImpl()
{
	m_documentEditContext->SetTitleEdit(m_oldTitle);
}
