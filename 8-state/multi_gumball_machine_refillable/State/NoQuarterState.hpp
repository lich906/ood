#pragma once

#include <iostream>

#include "IState.h"
#include "../IGumballMachine.h"

class NoQuarterState : public IState
{
public:
	NoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		IncrementQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	void Refill(unsigned count) override
	{
		m_gumballMachine.RefillWithBalls(count);
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	void IncrementQuarter()
	{
		m_gumballMachine.SetQuarterCount(m_gumballMachine.GetQuarterCount() + 1);
	}

	IGumballMachine& m_gumballMachine;
};
