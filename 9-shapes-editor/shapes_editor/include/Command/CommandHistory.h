#pragma once

#include <memory>
#include <vector>

#include "Command.h"

class CommandHistory
{
public:
	const static size_t HistoryDepthLimit = 50;

	void AddAndExecute(std::unique_ptr<Command>&& command);

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
