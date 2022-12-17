#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "IGumballMachine.h"
#include "State/SoldOutState.hpp"

using namespace fakeit;

TEST_CASE("Sold out state")
{
	Mock<IGumballMachine> gmMock;
	SoldOutState state(gmMock.get());
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting quarter, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.InsertQuarter();

		REQUIRE(capture() == "You can't insert a quarter, the machine is sold out\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting quarter, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "You can't eject, you haven't inserted a quarter yet\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.TurnCrank();

		REQUIRE(capture() == "You turned but there's no gumballs\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Dispensing, warning should be shown, state shouldn't change")
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
		REQUIRE(state.ToString() == "sold out");
	}
}
