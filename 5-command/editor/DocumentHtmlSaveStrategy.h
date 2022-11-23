#pragma once

#include "IDocumentSaveStrategy.h"

class DocumentHtmlSaveStrategy : public IDocumentSaveStrategy
{
public:
	void Save(std::filesystem::path path, const IDocument* document) override;
};
