#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
{
}

void SetTitleCommand::ExecuteImpl()
{
	m_onExecute();
}

void SetTitleCommand::UnexecuteImpl()
{
	m_onUnexecute();
}
