#pragma once

#include "IImage.h"
#include "CommandExecutionException.h"
#include "IDocumentEditContext.h"

class Image : public IImage
{
public:
	Image(IDocumentEditContext* documentEditCtx, std::filesystem::path path, int width, int height);

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int w, int h) override;

private:
	bool IsValidSize(int w, int h) const;

	const int MIN_DIMENSION_SIZE = 1;
	const int MAX_DIMENSION_SIZE = 10000;

	IDocumentEditContext* const m_documentEditContext;
	std::filesystem::path m_path;
	int m_width, m_height;
};
