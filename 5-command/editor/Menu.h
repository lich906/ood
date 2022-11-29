#pragma once

#include <iostream>
#include <unordered_map>

#include "CommandExecutionException.h"
#include "MenuItem.h"

class Menu
{
public:
	explicit Menu(std::istream& input = std::cin);

	void AddItem(const MenuItem& item);

	void ShowHelpMessage();

	void Run();

	void Exit();
	
private:
	bool m_exit = false;

	std::unordered_map<std::string, MenuItem> m_items;
	std::istream& m_input;
};
