#pragma once

#include <memory>

#include "IImage.h"
#include "IParagraph.h"

class ConstDocumentItem
{
public:
	ConstDocumentItem(const std::shared_ptr<const IImage>& imagePtr);

	ConstDocumentItem(const std::shared_ptr<const IParagraph>& paragraphPtr);

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~ConstDocumentItem() = default;

private:
	std::shared_ptr<const IImage> m_imagePtr = nullptr;
	std::shared_ptr<const IParagraph> m_paragraphPtr = nullptr;
};
