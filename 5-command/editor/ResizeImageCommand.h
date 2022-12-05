#pragma once

#include <functional>

#include "Command.h"

class ResizeImageCommand : public Command
{
public:
	ResizeImageCommand(std::function<void()> onExecute, std::function<void()> onUnexecute);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::function<void()> m_onExecute, m_onUnexecute;
};
