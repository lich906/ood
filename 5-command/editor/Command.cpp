#include "Command.h"

void Command::Execute()
{
	if (!m_executed)
	{
		ExecuteImpl();
		m_executed = true;
	}
	else
	{
		throw std::logic_error("Unable to execute command: command already have been executed");
	}
}

void Command::Unexecute()
{
	if (m_executed)
	{
		UnexecuteImpl();
		m_executed = false;
	}
	else
	{
		throw std::logic_error("Unable to unexecute command: command haven't been executed yet");
	}
}

void Command::Destroy() noexcept
{
}
