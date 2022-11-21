#pragma once

#include "IDocumentSaveStrategy.h"

class DocumentHtmlSaveStrategy : public IDocumentSaveStrategy
{
public:
	void Save(std::filesystem::path path, const std::shared_ptr<const IDocument>& document) override;
};
