#pragma once

#include <stdexcept>

struct CommandExecutionException : public std::exception
{
	explicit CommandExecutionException(const char* message)
		: std::exception(message){};

	explicit CommandExecutionException(const std::string& message)
		: std::exception(message.data()){};
};
