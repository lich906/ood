#pragma once

#include <iostream>
#include <unordered_map>

#include "MenuItem.h"

class Menu
{
public:
	void AddItem(MenuItem&& item);

	void ShowHelpMessage();

	void Run();
	
private:
	std::unordered_map<std::string, MenuItem> m_items;
};
