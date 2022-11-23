#pragma once

#include "Command.h"

class InsertParagraphCommand : public Command
{
public:
	InsertParagraphCommand(IDocumentEditContext* document, const std::shared_ptr<IParagraph>& paragraph,
		std::optional<size_t> position = std::nullopt);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::optional<size_t> m_index;
};
