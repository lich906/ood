#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "IGumballMachine.h"
#include "State/NoQuarterState.hpp"

using namespace fakeit;

TEST_CASE("No quarter state")
{
	Mock<IGumballMachine> gmMock;
	NoQuarterState state(gmMock.get());
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));

	SECTION("Inserting quarter, quarter count should increment, state should be changed to has quarter")
	{
		unsigned quarterCountBefore = 2;
		unsigned quarterCountAfter = 3;
		CaptureStdoutOutput capture;
		When(Method(gmMock, GetQuarterCount)).Return(quarterCountBefore);
		Fake(Method(gmMock, SetQuarterCount));

		state.InsertQuarter();

		REQUIRE(capture() == "You inserted a quarter\n");
		Verify(Method(gmMock, SetHasQuarterState)).Once();
		Verify(Method(gmMock, SetQuarterCount).Using(quarterCountAfter)).Once();

		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Ejecting quarter, warning should appear, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.EjectQuarter();

		REQUIRE(capture() == "You haven't inserted a quarter\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Turning crank, warning should appear, state shouldn't be changed")
	{
		CaptureStdoutOutput capture;

		state.TurnCrank();

		REQUIRE(capture() == "You turned but there's no quarter\n");
		Verify(Method(gmMock, SetHasQuarterState)).Never();
		Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
		Verify(Method(gmMock, SetNoQuarterState)).Never();
		Verify(Method(gmMock, SetSoldState)).Never();
		Verify(Method(gmMock, SetSoldOutState)).Never();
	}

	SECTION("Dispensing, warning should appear, state shouldn't be changed")
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

	SECTION("Get state string description")
	{
		REQUIRE(state.ToString() == "waiting for quarter");
	}
}
