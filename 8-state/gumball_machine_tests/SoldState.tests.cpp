#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "IGumballMachine.h"
#include "State/SoldState.hpp"

using namespace fakeit;

TEST_CASE("Sold state")
{
	Mock<IGumballMachine> gmMock;
	SoldState state(gmMock.get());
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting quarter, warning should be shown, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.InsertQuarter();

		REQUIRE(capture() == "Please wait, we're already giving you a gumball\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting quarter, warning should be shown, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "Sorry you already turned the crank\n");
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, warning should be shown, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.TurnCrank();

		REQUIRE(capture() == "Turning twice doesn't get you another gumball\n");
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	// This invokation should not be happen in normal workflow
	SECTION("Dispensing when gumball machine ran out of balls, ReleaseBall() invoked, state should be changed to sold out")
	{
		CaptureStdoutOutput capture;
		Fake(Method(gmMock, ReleaseBall));
		When(Method(gmMock, GetBallCount)).Return(0);

		state.Dispense();

		REQUIRE(capture() == "Oops, out of gumballs\n");
		Verify(Method(gmMock, SetSoldOutState)).Once();
		Verify(Method(gmMock, ReleaseBall)).Once();

		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
	}

	SECTION("Dispensing when machine has balls, ReleaseBall() invoked, state should be changed to no quarter")
	{
		CaptureStdoutOutput capture;
		Fake(Method(gmMock, ReleaseBall));
		When(Method(gmMock, GetBallCount)).Return(15);

		state.Dispense();

		REQUIRE(capture() == "");
		Verify(Method(gmMock, SetNoQuarterState)).Once();
		Verify(Method(gmMock, ReleaseBall)).Once();

		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Get state string description")
	{
		REQUIRE(state.ToString() == "delivering a gumball");
	}
}
