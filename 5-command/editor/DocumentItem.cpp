#include "DocumentItem.h"

DocumentItem::DocumentItem(const std::shared_ptr<IImage>& imagePtr)
	: ConstDocumentItem(imagePtr)
	, m_imagePtr(imagePtr)
{
}

DocumentItem::DocumentItem(const std::shared_ptr<IParagraph>& paragraphPtr)
	: ConstDocumentItem(paragraphPtr)
	, m_paragraphPtr(paragraphPtr)
{
}

std::shared_ptr<IImage> DocumentItem::GetImage()
{
	return m_imagePtr;
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
	return m_paragraphPtr;
}
