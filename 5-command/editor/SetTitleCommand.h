#pragma once

#include "Command.h"

class SetTitleCommand : public Command
{
public:
	SetTitleCommand(IDocumentEditContext* document, const std::string& title, const std::string& oldTitle);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::string m_title;
	std::string m_oldTitle;
};