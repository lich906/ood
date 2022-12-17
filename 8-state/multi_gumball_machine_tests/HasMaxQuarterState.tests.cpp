#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "State/HasMaxQuarterState.hpp"
#include "IGumballMachine.h"

using namespace fakeit;

TEST_CASE("Has max quarter state")
{
	Mock<IGumballMachine> gmMock;
	HasMaxQuarterState state(gmMock.get());
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Trying insert more quarters, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.InsertQuarter();

		REQUIRE(capture() == "You can't insert more quarters, limit is reached\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting quarter, quarter count should become 0 and state should change to no quarter")
	{
		unsigned quarterCountBefore = 123;
		unsigned quarterCountAfter = 0;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore);
		Fake(Method(gmMock, SetQuarterCount));

		state.EjectQuarter();

		REQUIRE(capture() == "123 quarters returned\n");
		Verify(Method(gmMock, SetNoQuarterState)).Once();
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, quarter count should be decremented and state should change to sold")
	{
		unsigned quarterCountBefore = 5;
		unsigned quarterCountAfter = 4;
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

		REQUIRE(capture() == "You need to pay first\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("String representation of state")
	{
		REQUIRE(state.ToString() == "full of quarters waiting for turn of crank");
	}
}
