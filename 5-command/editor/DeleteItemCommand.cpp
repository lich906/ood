#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(std::function<void()> onExecute, std::function<void()> onUnexecute)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
{
}

void DeleteItemCommand::ExecuteImpl()
{
	m_onExecute();
}

void DeleteItemCommand::UnexecuteImpl()
{
	m_onUnexecute();
}
