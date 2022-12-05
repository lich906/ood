#pragma once

#include <functional>

#include "Command.h"

class SetTitleCommand : public Command
{
public:
	SetTitleCommand(std::function<void()> onExecute, std::function<void()> onUnexecute);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::function<void()> m_onExecute, m_onUnexecute;
};
