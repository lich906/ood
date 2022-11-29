#pragma once

#include <iostream>

#include "Image.h"
#include "Command.h"
#include "PathConstants.h"

class InsertImageCommand : public Command
{
public:
	InsertImageCommand(IDocumentEditContext* document, const std::shared_ptr<IImage>& image,
		std::optional<size_t> position = std::nullopt);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

	void Destroy() noexcept override;

private:
	std::shared_ptr<IImage> CreateImageTempCopy(const std::shared_ptr<IImage>& image) const;

	std::shared_ptr<IImage> m_image;
	std::optional<size_t> m_position;

	std::filesystem::path m_tmpCopyFilename;

	static inline size_t m_tmpImageCopyIndex = 0;
};
