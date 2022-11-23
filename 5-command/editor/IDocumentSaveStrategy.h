#pragma once

#include <filesystem>

#include "IDocument.h"

class IDocumentSaveStrategy
{
public:
	virtual void Save(std::filesystem::path path, const IDocument* document) = 0;

	virtual ~IDocumentSaveStrategy() = default;
};
