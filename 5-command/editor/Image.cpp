#include "Image.h"

Image::Image(IDocumentEditContext* documentEditCtx, std::filesystem::path path, int width, int height)
	: m_documentEditContext(documentEditCtx)
	, m_path(std::move(path))
{
	if (!IsValidSize(width, height))
	{
		throw CommandExecutionException("Unable to change image size: unacceptable size");
	}

	m_width = width;
	m_height = height;
}

std::filesystem::path Image::GetPath() const
{
	return m_path;
}

int Image::GetWidth() const
{
	return m_width;
}

int Image::GetHeight() const
{
	return m_height;
}

void Image::Resize(int w, int h)
{
	if (!IsValidSize(w, h))
	{
		throw CommandExecutionException("Unable to change image size: unacceptable size");
	}

	m_documentEditContext->ResizeImage(m_width, m_height, w, h);
}

bool Image::IsValidSize(int w, int h) const
{
	if (w < MIN_DIMENSION_SIZE || w > MAX_DIMENSION_SIZE || h < MIN_DIMENSION_SIZE || h > MAX_DIMENSION_SIZE)
	{
		return false;
	}

	return true;
}
