#pragma once

#include <functional>

#include "Command.h"

class FunctionalCommand : public Command
{
public:
	FunctionalCommand(std::function<void()> onExecute, std::function<void()> onUnexecute);

private:
	void ExecuteImpl() override;

	void UnexecuteImpl() override;

	std::function<void()> m_onExecuteFn;
	std::function<void()> m_onUnexecuteFn;
};
