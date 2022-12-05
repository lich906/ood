#pragma once

#include <functional>

#include "IImage.h"
#include "CommandExecutionException.h"
#include "ResizeImageCommand.h"

class Image : public IImage
{
public:
	Image(std::filesystem::path path, int width, int height, std::function<void(std::unique_ptr<Command>&&)> commandSaver);

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int w, int h) override;

private:
	bool IsValidSize(int w, int h) const;

	const int MIN_DIMENSION_SIZE = 1;
	const int MAX_DIMENSION_SIZE = 10000;

	std::filesystem::path m_path;
	int m_width, m_height;
	std::function<void(std::unique_ptr<Command>&&)> m_commandSaver;
};
