#include "Command/FunctionalCommand.h"

FunctionalCommand::FunctionalCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecuteFn(std::move(onExecute))
	, m_onUnexecuteFn(std::move(onUnexecute))
{
}

void FunctionalCommand::ExecuteImpl()
{
	m_onExecuteFn();
}

void FunctionalCommand::UnexecuteImpl()
{
	m_onUnexecuteFn();
}
