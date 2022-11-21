#pragma once

#include <stdexcept>

struct CommandExecutionException : public std::exception
{
	CommandExecutionException(const char* message)
		: std::exception(message){};
};
