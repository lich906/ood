#include <catch.hpp>

#include "CaptureStdoutOutput.hpp"
#include "NaiveGumBallMachine.h"

TEST_CASE("Fill machine with quarters and turnk crank until there's no quarters left")
{
	naive::CGumballMachine gm(100500);
	CaptureStdoutOutput capture;

	for (unsigned i = 0; i < naive::CGumballMachine::QuarterCountLimit; ++i)
		gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
Machine is full of quarters
)");

	for (unsigned i = 0; i < naive::CGumballMachine::QuarterCountLimit; ++i)
		gm.TurnCrank();

	REQUIRE(capture() == R"(You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
)");

	gm.TurnCrank();

	REQUIRE(capture() == "You turned but there's no quarter\n");

	gm.EjectQuarter();

	REQUIRE(capture() == "You haven't inserted a quarter\n");
}

TEST_CASE("Fill machine with quarters and eject all quarters")
{
	naive::CGumballMachine gm(100500);
	CaptureStdoutOutput capture;

	for (unsigned i = 0; i < naive::CGumballMachine::QuarterCountLimit; ++i)
		gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
Machine is full of quarters
)");

	gm.EjectQuarter();

	REQUIRE(capture() == "5 quarters returned\n");

	gm.EjectQuarter();

	REQUIRE(capture() == "You haven't inserted a quarter\n");
}

TEST_CASE("Fill machine with quarters when gumballs count less than quarters count, we should be able to return unused quarters")
{
	naive::CGumballMachine gm(3);
	CaptureStdoutOutput capture;

	for (unsigned i = 0; i < naive::CGumballMachine::QuarterCountLimit; ++i)
		gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
Machine is full of quarters
)");

	for (unsigned i = 0; i < naive::CGumballMachine::QuarterCountLimit; ++i)
		gm.TurnCrank();

	REQUIRE(capture() == R"(You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
Oops, out of gumballs
You turned but there's no gumballs
You turned but there's no gumballs
)");

	gm.InsertQuarter();

	REQUIRE(capture() == "You can't insert a quarter, the machine is sold out\n");

	gm.EjectQuarter();

	REQUIRE(capture() == "2 quarters returned\n");

	gm.EjectQuarter();

	REQUIRE(capture() == "You haven't inserted a quarter\n");
}

TEST_CASE("Insert some quarters after used some")
{
	naive::CGumballMachine gm(100500);
	CaptureStdoutOutput capture;

	gm.InsertQuarter();
	gm.InsertQuarter();
	gm.InsertQuarter();

	REQUIRE(capture() == R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
)");

	gm.TurnCrank();
	gm.TurnCrank();

	REQUIRE(capture() == R"(You turned...
A gumball comes rolling out the slot...
You turned...
A gumball comes rolling out the slot...
)");

	// At this moment, there's one quarter left in machine

	gm.InsertQuarter();

	REQUIRE(capture() == "You inserted a quarter\n");

	gm.TurnCrank();

	REQUIRE(capture() == R"(You turned...
A gumball comes rolling out the slot...
)");

	gm.EjectQuarter();

	REQUIRE(capture() == "1 quarter returned\n");
}
