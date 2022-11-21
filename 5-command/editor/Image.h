#pragma once

#include "IImage.h"

class Image : public IImage
{
public:
	Image(std::filesystem::path path, int width, int height);

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	std::filesystem::path m_path;
	int m_width, m_height;
};
