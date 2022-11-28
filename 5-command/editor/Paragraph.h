#pragma once

#include "IParagraph.h"
#include "IDocumentEditContext.h"

class Paragraph : public IParagraph
{
public:
	Paragraph(IDocumentEditContext* documentEditCtx, size_t index, std::string text);

	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	IDocumentEditContext* const m_documentEditContext;
	std::string m_text;
	size_t m_position;
};
