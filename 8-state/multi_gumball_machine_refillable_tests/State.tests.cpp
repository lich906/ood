#include <catch.hpp>
#include <fakeit.hpp>

#include "CaptureStdoutOutput.hpp"
#include "IGumballMachine.h"
#include "State/SoldState.hpp"
#include "State/NoQuarterState.hpp"
#include "State/HasQuarterState.hpp"
#include "State/HasMaxQuarterState.hpp"
#include "State/SoldOutState.hpp"

using namespace fakeit;

TEST_CASE("Refill in sold state, warning should appear, state shouldn't change")
{
	Mock<IGumballMachine> gmMock;
	SoldState state(gmMock.get());
	CaptureStdoutOutput capture;
	Fake(Method(gmMock, RefillWithBalls));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));

	state.Refill(123);
	
	REQUIRE(capture() == "Can't refill while gumball rolling out\n");
	Verify(Method(gmMock, RefillWithBalls)).Never();
	Verify(Method(gmMock, SetSoldState)).Never();
	Verify(Method(gmMock, SetSoldOutState)).Never();
	Verify(Method(gmMock, SetHasQuarterState)).Never();
	Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
	Verify(Method(gmMock, SetNoQuarterState)).Never();
}

TEST_CASE("Refill in no quarter state, RefillWithBalls should be invoked, state shouldn't change")
{
	Mock<IGumballMachine> gmMock;
	NoQuarterState state(gmMock.get());
	CaptureStdoutOutput capture;
	Fake(Method(gmMock, RefillWithBalls));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	unsigned ballsCount = 123;

	state.Refill(ballsCount);

	REQUIRE(capture() == "");
	Verify(Method(gmMock, RefillWithBalls).Using(ballsCount)).Once();
	Verify(Method(gmMock, SetSoldState)).Never();
	Verify(Method(gmMock, SetSoldOutState)).Never();
	Verify(Method(gmMock, SetHasQuarterState)).Never();
	Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
	Verify(Method(gmMock, SetNoQuarterState)).Never();
}

TEST_CASE("Refill in has quarter state, RefillWithBalls should be invoked, state shouldn't change")
{
	Mock<IGumballMachine> gmMock;
	HasQuarterState state(gmMock.get());
	CaptureStdoutOutput capture;
	Fake(Method(gmMock, RefillWithBalls));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	unsigned ballsCount = 123;

	state.Refill(ballsCount);

	REQUIRE(capture() == "");
	Verify(Method(gmMock, RefillWithBalls).Using(ballsCount)).Once();
	Verify(Method(gmMock, SetSoldState)).Never();
	Verify(Method(gmMock, SetSoldOutState)).Never();
	Verify(Method(gmMock, SetHasQuarterState)).Never();
	Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
	Verify(Method(gmMock, SetNoQuarterState)).Never();
}

TEST_CASE("Refill in has max quarter state, RefillWithBalls should be invoked, state shouldn't change")
{
	Mock<IGumballMachine> gmMock;
	HasMaxQuarterState state(gmMock.get());
	CaptureStdoutOutput capture;
	Fake(Method(gmMock, RefillWithBalls));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	unsigned ballsCount = 123;

	state.Refill(ballsCount);

	REQUIRE(capture() == "");
	Verify(Method(gmMock, RefillWithBalls).Using(ballsCount)).Once();
	Verify(Method(gmMock, SetSoldState)).Never();
	Verify(Method(gmMock, SetSoldOutState)).Never();
	Verify(Method(gmMock, SetHasQuarterState)).Never();
	Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
	Verify(Method(gmMock, SetNoQuarterState)).Never();
}

TEST_CASE("Refill in sold out state, RefillWithBalls should be invoked, state shouldn't change")
{
	Mock<IGumballMachine> gmMock;
	SoldOutState state(gmMock.get());
	CaptureStdoutOutput capture;
	Fake(Method(gmMock, RefillWithBalls));
	Fake(Method(gmMock, SetSoldState));
	Fake(Method(gmMock, SetSoldOutState));
	Fake(Method(gmMock, SetHasQuarterState));
	Fake(Method(gmMock, SetHasMaxQuarterState));
	Fake(Method(gmMock, SetNoQuarterState));
	unsigned ballsCount = 123;

	state.Refill(ballsCount);

	REQUIRE(capture() == "");
	Verify(Method(gmMock, RefillWithBalls).Using(ballsCount)).Once();
	Verify(Method(gmMock, SetSoldState)).Never();
	Verify(Method(gmMock, SetSoldOutState)).Never();
	Verify(Method(gmMock, SetHasQuarterState)).Never();
	Verify(Method(gmMock, SetHasMaxQuarterState)).Never();
	Verify(Method(gmMock, SetNoQuarterState)).Never();
}
