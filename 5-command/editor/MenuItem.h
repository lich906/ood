#pragma once

#include <string>
#include <vector>
#include <functional>

struct MenuItem
{
	std::string shortcut;
	std::vector<std::string> argNames;
	std::string description;
	std::function<void()> callback;
};
