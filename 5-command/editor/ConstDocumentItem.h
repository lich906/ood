#pragma once

#include <memory>

#include "IImage.h"
#include "IParagraph.h"

class ConstDocumentItem
{
public:
	ConstDocumentItem(const std::shared_ptr<const IImage>& imagePtr);

	ConstDocumentItem(const std::shared_ptr<const IParagraph>& paragraphPtr);

	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~ConstDocumentItem() = default;

private:
	std::shared_ptr<const IImage> m_imagePtr = nullptr;
	std::shared_ptr<const IParagraph> m_paragraphPtr = nullptr;
};
