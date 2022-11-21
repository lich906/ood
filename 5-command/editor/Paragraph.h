#pragma once

#include "IParagraph.h"

class Paragraph : public IParagraph
{
public:
	Paragraph(std::string text);

	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
};
