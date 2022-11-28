#pragma once

#include <memory>
#include <optional>
#include <filesystem>

#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem.h"

class IDocumentEditContext
{
public:
	virtual std::shared_ptr<IParagraph> InsertParagraphEdit(const std::shared_ptr<IParagraph>& paragraph,
		std::optional<size_t> position = std::nullopt) = 0;

	virtual std::shared_ptr<IImage> InsertImageEdit(const std::shared_ptr<IImage>& image,
		std::optional<size_t> position = std::nullopt) = 0;

	virtual void DeleteItemEdit(size_t index) = 0;

	virtual void SetTitleEdit(const std::string& title) = 0;

	virtual void DeleteLastItemEdit() = 0;

	virtual void RecoverDeletedItem(size_t index, const DocumentItem& item) = 0;

	virtual DocumentItem& GetItemForEdit(size_t index) = 0;

	virtual void ReplaceParagraphText(size_t index, std::string& textRef, const std::string& text) = 0;

	virtual void ResizeImage(int& widthRef, int& heightRef, int width, int height) = 0;

	virtual ~IDocumentEditContext() = default;
};
