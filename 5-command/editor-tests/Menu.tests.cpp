#include <catch.hpp>
#include <sstream>

#include "Menu.h"

TEST_CASE("Menu prints menu items info to std::cout with ShowHelpMessage() method")
{
	std::ostringstream strCout;
	std::streambuf* coutBufPtr = std::cout.rdbuf();
	std::cout.rdbuf(strCout.rdbuf());

	SECTION("Adding some items and invoke ShowHelpMessage()")
	{
		Menu menu;
		menu.AddItem({ "Cmd", { "arg1", "arg2" }, "Cmd description", []() {} });
		menu.AddItem({ "Kommando", { "Argument1", "Argument2" }, "Ny tipa", []() {} });

		menu.ShowHelpMessage();

		REQUIRE(strCout.str() == "Available commands:\n"
							 "Cmd arg1 arg2\t\tCmd description\n"
							 "Kommando Argument1 Argument2\t\tNy tipa\n");
	}

	std::cout.rdbuf(coutBufPtr);
}

TEST_CASE("Running Menu invokes item's callbacks when item shortuct is recognized in input stream")
{
	std::ostringstream strCout;
	std::streambuf* coutBufPtr = std::cout.rdbuf();
	std::cout.rdbuf(strCout.rdbuf());

	SECTION("Should invoke lambda for existing command 'Cmd', should print message about unexisting command to std::cout")
	{
		std::istringstream iss("Cmd unknown\n");
		Menu menu(iss);
		menu.AddItem({ "Cmd", {}, "Description", [&]() { std::cout << "Lambda invoked" << std::endl; } });

		menu.Run();

		REQUIRE(strCout.str() == "Lambda invoked\n"
								 "Unknown command 'unknown'\n");
	}

	SECTION("Item's lambdas are invoked in correct order")
	{
		std::istringstream iss("First Second What Third\n");
		Menu menu(iss);
		menu.AddItem({ "First", {}, "Description", [&]() { std::cout << "First invoked" << std::endl; } });
		menu.AddItem({ "Second", {}, "Description", [&]() { std::cout << "Second invoked" << std::endl; } });
		menu.AddItem({ "Third", {}, "Description", [&]() { std::cout << "Third invoked" << std::endl; } });

		menu.Run();

		REQUIRE(strCout.str() == "First invoked\n"
								 "Second invoked\n"
								 "Unknown command 'What'\n"
								 "Third invoked\n");
	}

	std::cout.rdbuf(coutBufPtr);
}
