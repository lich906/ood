#pragma once

#include <iostream>

#include "IState.h"
#include "../IGumballMachine.h"

class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (auto quarterCount = m_gumballMachine.GetQuarterCount())
		{
			std::cout << std::format("{} quarter{} returned\n", quarterCount, quarterCount != 1 ? "s" : "");
			m_gumballMachine.SetQuarterCount(0);
		}
		else
		{
			std::cout << "There's no quarters to eject\n";
		}
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
};
