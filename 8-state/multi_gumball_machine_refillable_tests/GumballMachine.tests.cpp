#include <catch.hpp>
#include <fakeit.hpp>

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
)",
			m_count, (m_count != 1 ? "s" : ""), m_state);

		return subject.ToString() == expectedRepresentation;
	}

	std::string describe() const override
	{
		return std::format(R"(
Balls count: {}
State: {}
)",
			m_count, m_state);
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
const std::string HasMaxQuarterState = "full of quarters waiting for turn of crank";


TEST_CASE("Refill gumball machine when there's no balls")
{
	GumballMachine gm(0);

	SECTION("Refill with some gumballs, machine should go to no quarter state")
	{
		CaptureStdoutOutput capture;

		gm.Refill(5);

		REQUIRE(capture() == "Refill machine with 5 gumballs\n");
		REQUIRE_THAT(gm, CompareGumballMachine(5, NoQuarterState));
	}

	SECTION("Put one gumball in machine, machine should go to no quarter state")
	{
		CaptureStdoutOutput capture;

		gm.Refill(1);

		REQUIRE(capture() == "Refill machine with 1 gumball\n");
		REQUIRE_THAT(gm, CompareGumballMachine(1, NoQuarterState));
	}

	SECTION("Refill with zero gumballs (empty machine), machine stays in sold out state")
	{
		CaptureStdoutOutput capture;

		gm.Refill(0);

		REQUIRE(capture() == "All gumballs removed from machine\n");
		REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));
	}
}

TEST_CASE("Insert some quarters, then remove balls from machine, user should be able to eject inserted quarters")
{
	CaptureStdoutOutput capture;
	GumballMachine gm(100500);

	REQUIRE_THAT(gm, CompareGumballMachine(100500, NoQuarterState));

	gm.InsertQuarter();
	gm.InsertQuarter();
	gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
)");
	REQUIRE_THAT(gm, CompareGumballMachine(100500, HasQuarterState));

	gm.Refill(0);

	REQUIRE(capture() == "All gumballs removed from machine\n");
	REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));

	gm.EjectQuarter();

	REQUIRE(capture() == "3 quarters returned\n");
	REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));
}

TEST_CASE("Refill machine when it has max quarters")
{
	CaptureStdoutOutput capture;
	GumballMachine gm(100500);

	for (unsigned i = 0; i < HasQuarterState::QuarterCountLimit; ++i)
		gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
Machine is full of quarters
)");
	REQUIRE_THAT(gm, CompareGumballMachine(100500, HasMaxQuarterState));

	SECTION("Refilling, machine should stay in the same state")
	{
		gm.Refill(20);

		REQUIRE(capture() == "Refill machine with 20 gumballs\n");
		REQUIRE_THAT(gm, CompareGumballMachine(20, HasMaxQuarterState));
	}

	SECTION("Emptying, machine should go to sold out state")
	{
		gm.Refill(0);

		REQUIRE(capture() == "All gumballs removed from machine\n");
		REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));
	}
}

TEST_CASE("Refill machine when it has quarters")
{
	CaptureStdoutOutput capture;
	GumballMachine gm(100500);

	gm.InsertQuarter();
	gm.InsertQuarter();
	gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
)");
	REQUIRE_THAT(gm, CompareGumballMachine(100500, HasQuarterState));

	SECTION("Refilling, machine should stay in the same state")
	{
		gm.Refill(20);

		REQUIRE(capture() == "Refill machine with 20 gumballs\n");
		REQUIRE_THAT(gm, CompareGumballMachine(20, HasQuarterState));
	}

	SECTION("Emptying, machine should go to sold out state")
	{
		gm.Refill(0);

		REQUIRE(capture() == "All gumballs removed from machine\n");
		REQUIRE_THAT(gm, CompareGumballMachine(0, SoldOutState));
	}
}
