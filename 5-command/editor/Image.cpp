#include "Image.h"

Image::Image(std::filesystem::path path, int width, int height, std::function<void(std::unique_ptr<Command>&&)> commandSaver)
	: m_path(std::move(path))
	, m_commandSaver(commandSaver)
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

	std::unique_ptr<Command> command = std::make_unique<ResizeImageCommand>(
		[this, w, h]() {
			m_width = w;
			m_height = h;
		},
		[this, w = m_width, h = m_height]() {
			m_width = w;
			m_height = h;
		}
	);

	command->Execute();
	m_commandSaver(std::move(command));
}

bool Image::IsValidSize(int w, int h) const
{
	if (w < MIN_DIMENSION_SIZE || w > MAX_DIMENSION_SIZE || h < MIN_DIMENSION_SIZE || h > MAX_DIMENSION_SIZE)
	{
		return false;
	}

	return true;
}
