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
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting quarter, warning should be shown, state shouldn't change")
	{
		CaptureStdoutOutput capture;

		state.InsertQuarter();

		REQUIRE(capture() == "You can't insert a quarter, the machine is sold out\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting remaining quarters, all quarters ejected, state shouldn't change")
	{
		When(Method(gmMock, GetQuarterCount)).Return(100500);
		Fake(Method(gmMock, SetQuarterCount));
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "100500 quarters returned\n");
		Verify(Method(gmMock, SetQuarterCount).Using(0)).Once();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Trying eject quarters when there's no quarters, warning should be shown, state shoudn't change")
	{
		When(Method(gmMock, GetQuarterCount)).Return(0);
		Fake(Method(gmMock, SetQuarterCount));
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "There's no quarters to eject\n");
		Verify(Method(gmMock, SetQuarterCount)).Never();
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
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
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
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
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Get state string description")
	{
		REQUIRE(state.ToString() == "sold out");
	}
}
