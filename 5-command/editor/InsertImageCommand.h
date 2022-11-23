#pragma once

#include "Command.h"

class InsertImageCommand : public Command
{
public:
	InsertImageCommand(IDocumentEditContext* document, const std::shared_ptr<IImage>& image,
		std::optional<size_t> position = std::nullopt);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	std::shared_ptr<IImage> m_image;
	std::optional<size_t> m_index;
};
