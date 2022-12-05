#include "InsertParagraphCommand.h"

InsertParagraphCommand::InsertParagraphCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
{
}

void InsertParagraphCommand::ExecuteImpl()
{
	m_onExecute();
}

void InsertParagraphCommand::UnexecuteImpl()
{
	m_onUnexecute();
}
