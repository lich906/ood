#include "ReplaceTextCommand.h"

ReplaceTextCommand::ReplaceTextCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
{
}

void ReplaceTextCommand::ExecuteImpl()
{
	m_onExecute();
}

void ReplaceTextCommand::UnexecuteImpl()
{
	m_onUnexecute();
}
