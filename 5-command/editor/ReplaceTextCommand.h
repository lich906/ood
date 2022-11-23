#pragma once

#include "Command.h"

class ReplaceTextCommand : public Command
{
public:
	ReplaceTextCommand(IDocumentEditContext* document, size_t index,
		const std::string& text, const std::string& oldText);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	void ReplaceText(const std::string& text) const;

	size_t m_index;
	std::string m_text;
	std::string m_oldText;
};
