#pragma once

#include <vector>

#include "Command.h"
#include "CommandExecutionException.h"

class CommandHistory
{
public:
	const static size_t HistoryDepthLimit = 10;

	void AddCommand(std::unique_ptr<Command>&& command);

	void Redo();

	void Undo();

	bool CanUndo() const;

	bool CanRedo() const;

	~CommandHistory() noexcept;

private:
	bool DepthLimitReached() const;

	std::vector<std::unique_ptr<Command>> m_commands;
	int m_lastExecutedCommandIndex = -1;
	int m_lastUndoableCommandIndex = 0;
};
