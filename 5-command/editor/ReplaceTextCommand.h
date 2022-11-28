#pragma once

#include "Command.h"

class ReplaceTextCommand : public Command
{
public:
	ReplaceTextCommand(std::string& textRef, const std::string& oldText, const std::string& text);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	void ReplaceText(const std::string& text) const;

	std::string& m_textRef;
	std::string m_text;
	std::string m_oldText;
};
