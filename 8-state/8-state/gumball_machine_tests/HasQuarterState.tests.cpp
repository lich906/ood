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
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting quarter, warning should be shown, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.InsertQuarter();

		REQUIRE(capture() == "You can't insert another quarter\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting quarter, quarter returned successfully, state should be changed to no quarter")
	{
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "Quarter returned\n");
		Verify(Method(gmMock, SetNoQuarterState)).Once();

		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, we turned... , state should be changed to sold")
	{
		CaptureStdoutOutput capture;

		state.TurnCrank();

		REQUIRE(capture() == "You turned...\n");
		Verify(Method(gmMock, SetSoldState)).Once();

		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Dispensing, warning should appear, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.Dispense();

		REQUIRE(capture() == "No gumball dispensed\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Get state string description")
	{
		REQUIRE(state.ToString() == "waiting for turn of crank");
	}
}
