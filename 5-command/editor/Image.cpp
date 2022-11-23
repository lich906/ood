#include "Image.h"

Image::Image(std::filesystem::path path, int width, int height)
	: m_path(std::move(path))
	, m_width(width)
	, m_height(height)
{
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
	m_width = width;
	m_height = height;
}
