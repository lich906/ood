#pragma once

#include <filesystem>

#include "IDocument.h"

class IDocumentSaveStrategy
{
public:
	virtual void Save(std::filesystem::path path, const std::shared_ptr<const IDocument>& document) = 0;

	virtual ~IDocumentSaveStrategy() = default;
};
