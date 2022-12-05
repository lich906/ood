#include "Menu.h"

Menu::Menu(std::istream& input)
	: m_input(input)
{
}

void Menu::AddItem(const MenuItem& item)
{
	m_items.insert({ item.shortcut, item });
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
	for (std::string commandShortcut; !m_exit && (m_input >> commandShortcut);)
	{
		auto item = m_items.find(commandShortcut);

		if (item != m_items.end())
		{
			try
			{
				item->second.callback();
			}
			catch (const std::exception& e)
			{
				std::cout << "Error: " << e.what() << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown command '" << commandShortcut << '\'' << std::endl;
		}
	}
}

void Menu::Exit()
{
	std::cout << "Bye!" << std::endl;
	m_exit = true;
}
