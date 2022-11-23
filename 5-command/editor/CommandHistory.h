#pragma once

#include <vector>

#include "Command.h"
#include "CommandExecutionException.h"

class CommandHistory
{
public:
	const size_t HistoryDepthLimit = 10;

	void AddCommand(std::unique_ptr<Command>&& command);

	void Redo();

	void Undo();

	bool CanUndo() const;

	bool CanRedo() const;

private:
	std::vector<std::unique_ptr<Command>> m_commands;
	int8_t m_lastExecutedCommandIndex = -1;
};
