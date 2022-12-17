#pragma once

#include <iostream>

#include "IState.h"
#include "../IGumballMachine.h"

class HasMaxQuarterState : public IState
{
public:
	HasMaxQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert more quarters, limit is reached\n";
	}
	void EjectQuarter() override
	{
		std::cout << std::format("{} quarters returned\n", m_gumballMachine.GetQuarterCount());
		m_gumballMachine.SetQuarterCount(0);
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		DecrementQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "full of quarters waiting for turn of crank";
	}

private:
	void DecrementQuarter()
	{
		m_gumballMachine.SetQuarterCount(m_gumballMachine.GetQuarterCount() - 1);
	}

	IGumballMachine& m_gumballMachine;
};
