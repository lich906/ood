#include <catch.hpp>
#include <sstream>

#include "CaptureStdoutOutput.hpp"
#include "GumballMachine.h"

class GumballMachineMatcher : public Catch::Matchers::Impl::MatcherBase<GumballMachine>
{
public:
	GumballMachineMatcher(unsigned count, const std::string& state)
		: m_count(count)
		, m_state(state)
	{
	}

	bool match(const GumballMachine& subject) const override
	{
		auto expectedRepresentation = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)", m_count, (m_count != 1 ? "s" : ""), m_state);

		return subject.ToString() == expectedRepresentation;
	}

	std::string describe() const override
	{
		return std::format(R"(
Balls count: {}
State: {}
)", m_count, m_state);
	}

private:
	unsigned m_count;
	const std::string& m_state;
};

GumballMachineMatcher CompareGumballMachine(unsigned count, const std::string& state)
{
	return { count, state };
}

const std::string SoldOutState = "sold out";
const std::string SoldState = "delivering a gumball";
const std::string NoQuarterState = "waiting for quarter";
const std::string HasQuarterState = "waiting for turn of crank";

TEST_CASE("Gumball machine initialization")
{
	SECTION("Initialize with zero balls, machine should be in sold out state")
	{
		GumballMachine gm(0);

		REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));
	}

	SECTION("Initialize with some balls, machine should be in no quarter state")
	{
		GumballMachine gm(3);

		REQUIRE_THAT(gm, CompareGumballMachine(3, NoQuarterState));
	}

	SECTION("String representation of newely created machine with gumballs inside")
	{
		GumballMachine gm(100500);

		REQUIRE(gm.ToString() == R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 100500 gumballs
Machine is waiting for quarter
)");
	}

	SECTION("String representation of newely created empty machine")
	{
		GumballMachine gm(0);

		REQUIRE(gm.ToString() == R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Machine is sold out
)");
	}

	SECTION("Get string representation of newely created machine with single gumball")
	{
		GumballMachine gm(1);

		REQUIRE(gm.ToString() == R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 1 gumball
Machine is waiting for quarter
)");
	}
}



TEST_CASE("Getting gum ball from gumball machine containing single gum ball left")
{
	unsigned ballCount = 1;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.InsertQuarter();
		
	REQUIRE(captureStdout() == "You inserted a quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));

	gm.TurnCrank();

	REQUIRE(captureStdout() == "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount - 1, SoldOutState));
}

TEST_CASE("Getting gum ball from gumball machine containing many gumballs")
{
	unsigned ballCount = 100500;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.InsertQuarter();

	REQUIRE(captureStdout() == "You inserted a quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));

	gm.TurnCrank();

	REQUIRE(captureStdout() == "You turned...\nA gumball comes rolling out the slot...\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount - 1, NoQuarterState));
}

TEST_CASE("Inserting and ejecting quarter")
{
	unsigned ballCount = 3;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.InsertQuarter();

	REQUIRE(captureStdout() == "You inserted a quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));

	gm.EjectQuarter();

	REQUIRE(captureStdout() == "Quarter returned\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, NoQuarterState));

	SECTION("Trying to eject quarter again, attempt should fail")
	{
		gm.EjectQuarter();

		REQUIRE(captureStdout() == "You haven't inserted a quarter\n");
		REQUIRE_THAT(gm, CompareGumballMachine(ballCount, NoQuarterState));
	}

	SECTION("Inserting quarter again, should be fine")
	{
		gm.InsertQuarter();

		REQUIRE(captureStdout() == "You inserted a quarter\n");
		REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));
	}
}

TEST_CASE("Inserting quarter twice, machine shouldn't accept second quarter")
{
	unsigned ballCount = 3;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.InsertQuarter();

	REQUIRE(captureStdout() == "You inserted a quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));

	gm.InsertQuarter();

	REQUIRE(captureStdout() == "You can't insert another quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, HasQuarterState));
}

TEST_CASE("Turning crank without quarter inserted, nothing happens")
{
	unsigned ballCount = 3;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.TurnCrank();

	REQUIRE(captureStdout() == "You turned but there's no quarter\nYou need to pay first\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, NoQuarterState));
}

TEST_CASE("Acting with sold out gumball machine")
{
	unsigned ballCount = 0;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	SECTION("Inserting quarter should fail")
	{
		gm.InsertQuarter();

		REQUIRE(captureStdout() == "You can't insert a quarter, the machine is sold out\n");
		REQUIRE_THAT(gm, CompareGumballMachine(ballCount, SoldOutState));
	}

	SECTION("Turning crank, no gumballs dispensed")
	{
		gm.TurnCrank();

		REQUIRE(captureStdout() == "You turned but there's no gumballs\nNo gumball dispensed\n");
		REQUIRE_THAT(gm, CompareGumballMachine(ballCount, SoldOutState));
	}

	SECTION("Ejecting quarter, attempt should fail")
	{
		gm.EjectQuarter();

		REQUIRE(captureStdout() == "You can't eject, you haven't inserted a quarter yet\n");
		REQUIRE_THAT(gm, CompareGumballMachine(ballCount, SoldOutState));
	}
}

TEST_CASE("Ejecting quarter when there's no quarter, attempt should fail")
{
	unsigned ballCount = 3;
	GumballMachine gm(ballCount);

	CaptureStdoutOutput captureStdout;

	gm.EjectQuarter();

	REQUIRE(captureStdout() == "You haven't inserted a quarter\n");
	REQUIRE_THAT(gm, CompareGumballMachine(ballCount, NoQuarterState));
}
