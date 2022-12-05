#pragma once

#include <functional>

#include "Command.h"
#include "DocumentItem.h"

class DeleteItemCommand : public Command
{
public:
	DeleteItemCommand(std::function<void()> onExecute, std::function<void()> onUnexecute);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::function<void()> m_onExecute, m_onUnexecute;
};
