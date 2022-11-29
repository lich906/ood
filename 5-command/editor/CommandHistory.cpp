#include "CommandHistory.h"

void CommandHistory::AddCommand(std::unique_ptr<Command>&& command)
{
	if (CanRedo()) // destroy and remove redoable commands
	{
		for (size_t index = 1 + m_lastExecutedCommandIndex; index < m_commands.size(); ++index)
		{
			m_commands[index]->Destroy();
		}

		++m_lastExecutedCommandIndex;
		m_commands.resize(m_lastExecutedCommandIndex + 1);
		m_commands.back() = std::move(command);
	}
	else // inserting command back
	{
		if (DepthLimitReached())
		{
			++m_lastUndoableCommandIndex;
		}

		++m_lastExecutedCommandIndex;
		m_commands.emplace_back(std::move(command));
	}
}

void CommandHistory::Redo()
{
	if (!CanRedo())
	{
		throw CommandExecutionException("Unable to redo command: no commands available for redo");
	}

	m_commands[1 + m_lastExecutedCommandIndex++]->Execute();
}

void CommandHistory::Undo()
{
	if (!CanUndo())
	{
		throw CommandExecutionException("Unable to undo command: no commands available for undo");
	}
	
	m_commands[m_lastExecutedCommandIndex--]->Unexecute();
}

bool CommandHistory::CanUndo() const
{
	return m_lastExecutedCommandIndex >= m_lastUndoableCommandIndex;
}

bool CommandHistory::CanRedo() const
{
	return m_lastExecutedCommandIndex < static_cast<int>(m_commands.size() - 1);
}

CommandHistory::~CommandHistory() noexcept
{
	for (auto& command : m_commands)
	{
		command->Destroy();
	}
}

bool CommandHistory::DepthLimitReached() const
{
	return (m_lastExecutedCommandIndex - m_lastUndoableCommandIndex) == (HistoryDepthLimit - 1);
}
