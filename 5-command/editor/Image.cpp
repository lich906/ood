#include "Image.h"

Image::Image(std::filesystem::path path, int width, int height)
	: m_path(std::move(path))
{
	Resize(width, height);
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

void Image::Resize(int width, int height)
{
	if (width < MIN_DIMENSION_SIZE || width > MAX_DIMENSION_SIZE || height < MIN_DIMENSION_SIZE || height > MAX_DIMENSION_SIZE)
	{
		throw CommandExecutionException("Unable to change image size: unacceptable size");
	}

	m_width = width;
	m_height = height;
}
