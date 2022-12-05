#pragma once

#include "IParagraph.h"
#include "ReplaceTextCommand.h"

class Paragraph : public IParagraph
{
public:
	Paragraph(std::string text, std::function<void(std::unique_ptr<Command>&&)> commandSaver);

	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	// параграф не должен знать о своем индексе
	std::string m_text;
	std::function<void(std::unique_ptr<Command>&&)> m_commandSaver;
};
