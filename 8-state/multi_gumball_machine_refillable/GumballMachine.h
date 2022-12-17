#pragma once

#include <iostream>
#include <format>

#include "State/IState.h"
#include "State/SoldState.hpp"
#include "State/SoldOutState.hpp"
#include "State/HasQuarterState.hpp"
#include "State/HasMaxQuarterState.hpp"
#include "State/NoQuarterState.hpp"
#include "IGumballMachine.h"

class GumballMachine : private IGumballMachine
{
public:
	GumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_hasMaxQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
			m_count, m_count != 1 ? "s" : "", m_state->ToString());
	}
	void Refill(unsigned ballsCount)
	{
		m_state->Refill(ballsCount);
	}

private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	unsigned GetQuarterCount() const override
	{
		return m_quarterCount;
	}
	void SetQuarterCount(unsigned count) override
	{
		m_quarterCount = count;
	}
	void RefillWithBalls(unsigned count) override
	{
		if (m_count = count)
		{
			std::cout << std::format("Refill machine with {} gumball{}\n", count, count != 1 ? "s" : "");

			if (m_quarterCount == HasQuarterState::QuarterCountLimit)
			{
				SetHasMaxQuarterState();
			}
			else if (m_quarterCount)
			{
				SetHasQuarterState();
			}
			else
			{
				SetNoQuarterState();
			}
		}
		else
		{
			std::cout << "All gumballs removed from machine\n";
			SetSoldOutState();
		}
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}
	void SetHasMaxQuarterState() override
	{
		m_state = &m_hasMaxQuarterState;
	}

private:
	unsigned m_count = 0;
	unsigned m_quarterCount = 0;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	HasMaxQuarterState m_hasMaxQuarterState;
	IState* m_state;
};
