#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
{
}

void ResizeImageCommand::ExecuteImpl()
{
	m_onExecute();
}

void ResizeImageCommand::UnexecuteImpl()
{
	m_onUnexecute();
}
