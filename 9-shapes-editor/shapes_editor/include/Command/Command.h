#pragma once

#include <stdexcept>

class Command
{
public:
	virtual ~Command() = default;

	void Execute();

	void Unexecute();

	virtual void Destroy(){};

protected:
	virtual void ExecuteImpl() = 0;

	virtual void UnexecuteImpl() = 0;

private:
	bool m_executed = false;
};
