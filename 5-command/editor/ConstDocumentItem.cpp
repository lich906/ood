#include "ConstDocumentItem.h"

ConstDocumentItem::ConstDocumentItem(const std::shared_ptr<const IImage>& imagePtr)
	: m_imagePtr(imagePtr)
{
}

ConstDocumentItem::ConstDocumentItem(const std::shared_ptr<const IParagraph>& paragraphPtr)
	: m_paragraphPtr(paragraphPtr)
{
}

std::shared_ptr<const IImage> ConstDocumentItem::GetImage() const
{
	return m_imagePtr;
}

std::shared_ptr<const IParagraph> ConstDocumentItem::GetParagraph() const
{
	return m_paragraphPtr;
}
