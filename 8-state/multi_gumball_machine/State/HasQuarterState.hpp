#pragma once

#include <iostream>

#include "IState.h"
#include "../IGumballMachine.h"

class HasQuarterState : public IState
{
public:
	static const unsigned QuarterCountLimit = 5;

	HasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		IncrementQuarter();

		if (m_gumballMachine.GetQuarterCount() == QuarterCountLimit)
		{
			std::cout << "Machine is full of quarters\n";
			m_gumballMachine.SetHasMaxQuarterState();
		}
	}
	void EjectQuarter() override
	{
		auto quarterCount = m_gumballMachine.GetQuarterCount();
		std::cout << std::format("{} quarter{} returned\n", quarterCount, quarterCount != 1 ? "s" : "");
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
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	void DecrementQuarter()
	{
		m_gumballMachine.SetQuarterCount(m_gumballMachine.GetQuarterCount() - 1);
	}
	void IncrementQuarter()
	{
		m_gumballMachine.SetQuarterCount(m_gumballMachine.GetQuarterCount() + 1);
	}

	IGumballMachine& m_gumballMachine;
};
