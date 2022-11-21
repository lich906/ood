#include "Menu.h"

void Menu::AddItem(MenuItem&& item)
{
	m_items.insert({ item.shortcut, std::move(item) });
}

void Menu::ShowHelpMessage()
{
	std::cout << "Available commands:" << std::endl;

	for (auto& [shortcut, item] : m_items)
	{
		std::cout << shortcut;
		for (auto& arg : item.argNames)
		{
			std::cout << ' ' << arg;
		}
		std::cout << "\t\t" << item.description << std::endl;
	}
}

void Menu::Run()
{
	for (std::string commandShortcut; std::getline(std::cin, commandShortcut, ' ');)
	{
		std::cout << "> ";
		auto item = m_items.find(commandShortcut);

		if (item != m_items.end())
		{
			item->second.callback();
		}
		else
		{
			std::cout << "Unknown command '" << item->first << '\'' << std::endl;
		}
	}
}
