#include "CommandHistory.h"

void CommandHistory::AddCommand(std::unique_ptr<Command>&& command)
{
	if (CanRedo()) // remove undoable commands
	{
		++m_lastExecutedCommandIndex;
		m_commands.resize(m_lastExecutedCommandIndex);
		m_commands.back() = std::move(command);
	}
	else // inserting command back
	{
		if (m_commands.size() == HistoryDepthLimit)
		{
			m_commands.erase(m_commands.begin());
		}
		else
		{
			++m_lastExecutedCommandIndex;
		}

		m_commands.emplace_back(std::move(command));
	}
}

void CommandHistory::Redo()
{
	if (!CanRedo())
	{
		throw CommandExecutionException("Unable to redo command: no commands available for redo");
	}

	m_commands[m_lastExecutedCommandIndex + 1]->Execute();
	++m_lastExecutedCommandIndex;
}

void CommandHistory::Undo()
{
	if (!CanUndo())
	{
		throw CommandExecutionException("Unable to undo command: no commands stored in command history");
	}
	
	m_commands[m_lastExecutedCommandIndex]->Unexecute();
	--m_lastExecutedCommandIndex;
}

bool CommandHistory::CanUndo() const
{
	return m_lastExecutedCommandIndex >= 0;
}

bool CommandHistory::CanRedo() const
{
	return m_lastExecutedCommandIndex < static_cast<int8_t>(m_commands.size() - 1);
}
