#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "IGumballMachine.h"
#include "State/HasQuarterState.hpp"

using namespace fakeit;

TEST_CASE("Has quarter state")
{
	Mock<IGumballMachine> gmMock;
	HasQuarterState state(gmMock.get());
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting last available quarter, quarter count should increment, state should change to has max quarter")
	{
		unsigned quarterCountBefore = HasQuarterState::QuarterCountLimit - 1;
		unsigned quarterCountAfter = HasQuarterState::QuarterCountLimit;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore).Return(quarterCountAfter);
		Fake(Method(gmMock, SetQuarterCount));

		state.InsertQuarter();

		REQUIRE(capture() == "You inserted a quarter\nMachine is full of quarters\n");
		Verify(Method(gmMock, SetHasMaxQuarterState)).Once();
		Verify(Method(gmMock, GetQuarterCount)).Exactly(2);
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Inserting quarter, quarter count should increment, state shouldn't change")
	{
		unsigned quarterCountBefore = 3;
		unsigned quarterCountAfter = 4;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore).Return(quarterCountAfter);
		Fake(Method(gmMock, SetQuarterCount));

		state.InsertQuarter();

		REQUIRE(capture() == "You inserted a quarter\n");
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();
		Verify(Method(gmMock, GetQuarterCount)).Exactly(2);

		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting single quarter, quarter count should become 0, state should change to no quarter")
	{
		unsigned quarterCountBefore = 1;
		unsigned quarterCountAfter = 0;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore);
		Fake(Method(gmMock, SetQuarterCount));

		state.EjectQuarter();

		REQUIRE(capture() == "1 quarter returned\n");

		Verify(Method(gmMock, SetNoQuarterState)).Once();
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting many quarters, quarter count should become 0, state should change to no quarter")
	{
		unsigned quarterCountBefore = 3;
		unsigned quarterCountAfter = 0;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore);
		Fake(Method(gmMock, SetQuarterCount));

		state.EjectQuarter();

		REQUIRE(capture() == "3 quarters returned\n");
		Verify(Method(gmMock, SetNoQuarterState)).Once();
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, quarter count should be decremented and state should change to sold")
	{
		unsigned quarterCountBefore = 4;
		unsigned quarterCountAfter = 3;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore);
		Fake(Method(gmMock, SetQuarterCount));

		state.TurnCrank();

		REQUIRE(capture() == "You turned...\n");
		Verify(Method(gmMock, SetSoldState)).Once();
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Trying dispense, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.Dispense();

		REQUIRE(capture() == "No gumball dispensed\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("String representation of state")
	{
		REQUIRE(state.ToString() == "waiting for turn of crank");
	}
}
