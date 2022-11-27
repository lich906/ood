#pragma once

#include <fstream>
#include <unordered_map>
#include <algorithm>

#include "IDocumentSaveStrategy.h"
#include "PathConstants.h"

class DocumentHtmlSaveStrategy : public IDocumentSaveStrategy
{
public:
	void Save(std::filesystem::path path, const IDocument* document) override;

private:
	const std::unordered_map<char, std::string> m_encodeTable = {
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '"', "&quot;" },
		{ '\'', "&apos;" },
		{ '&', "&amp;" },
	};

	std::string GetHtmlEncodedString(const std::string& source) const;

	std::string GetParagraphHtml(const std::shared_ptr<const IParagraph>& paragraph) const;

	std::string GetImageHtml(const std::shared_ptr<const IImage>& image) const;

	void SaveImageFile(std::filesystem::path path, const std::shared_ptr<const IImage>& image) const;
};
