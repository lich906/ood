#pragma once

#include <format>
#include <iostream>

namespace naive
{
class CGumballMachine
{
public:
	static const unsigned QuarterCountLimit = 5;

	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть хотя бы одна монетка
		Sold, // Монетка выдана
		HasMaxQuarter, // Есть максимум монеток
	};

	CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			++m_quarterCount;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			cout << "You inserted a quarter\n";
			++m_quarterCount;
			if (m_quarterCount == QuarterCountLimit)
			{
				cout << "Machine is full of quarters\n";
				m_state = State::HasMaxQuarter;
			}
			break;
		case State::HasMaxQuarter:
			cout << "You can't insert more quarters, limit is reached\n";
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
		case State::HasMaxQuarter:
			cout << format("{} quarter{} returned\n", m_quarterCount, m_quarterCount != 1 ? "s" : "");
			m_quarterCount = 0;
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (m_quarterCount)
			{
				cout << format("{} quarter{} returned\n", m_quarterCount, m_quarterCount != 1 ? "s" : "");
				m_quarterCount = 0;
				m_state = State::NoQuarter;
			}
			else
			{
				cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
		case State::HasMaxQuarter:
			cout << "You turned...\n";
			--m_quarterCount;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString() const
	{
		std::string state;

		switch (m_state)
		{
		case naive::CGumballMachine::State::SoldOut:
			state = "sold out";
			break;
		case naive::CGumballMachine::State::NoQuarter:
			state = "waiting for quarter";
			break;
		case naive::CGumballMachine::State::HasQuarter:
			state = "waiting for turn of crank";
			break;
		case naive::CGumballMachine::State::Sold:
			state = "delivering a gumball";
			break;
		case naive::CGumballMachine::State::HasMaxQuarter:
			state = "full of quarters waiting for turn of crank";
			break;
		default:
			break;
		}

		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)", m_count, (m_count != 1 ? "s" : ""), state);
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot...\n";
			--m_count;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else if (m_quarterCount)
			{
				m_state = State::HasQuarter;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	unsigned m_quarterCount = 0;
	unsigned m_count; // Количество шариков
	State m_state = State::SoldOut;
};
} // namespace naive
