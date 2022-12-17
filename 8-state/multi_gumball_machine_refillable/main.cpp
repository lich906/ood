#include "MenuFP.h"
#include "GumballMachine.h"

int main()
{
	GumballMachine machine(0);

	CMenuFP menu;

	menu.AddItem("info", "prints info about gumball machine", [&machine]() {
		std::cout << machine.ToString();
	});
	menu.AddItem("insert-quarter", "insert quarter in gumball machine", std::bind(&GumballMachine::InsertQuarter, &machine));
	menu.AddItem("eject-quarter", "eject all quarters from gumball machine", std::bind(&GumballMachine::EjectQuarter, &machine));
	menu.AddItem("turn-crank", "turn crank and possibly get a gumball", std::bind(&GumballMachine::TurnCrank, &machine));
	menu.AddItem("refill", "refill machine with gumballs or empty it", [&machine]() {
		std::cout << "How many gumballs you want to load to machine? (postive integer or 0 to empty)\n>";
		std::string str;
		std::getline(std::cin, str);
		machine.Refill(std::stoul(str));
	});
	menu.AddItem("exit", "exit current program", std::bind(&CMenuFP::Exit, &menu));
	menu.AddItem("help", "prints help message", std::bind(&CMenuFP::ShowInstructions, &menu));

	menu.Run();

	return 0;
}
