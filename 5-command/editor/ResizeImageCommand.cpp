#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(int& widthRef, int& heightRef, int width, int height)
	: Command(nullptr)
	, m_widthRef(widthRef)
	, m_heightRef(heightRef)
	, m_width(width), m_height(height)
{
}

void ResizeImageCommand::ExecuteImpl()
{
	SwapSize();
}

void ResizeImageCommand::UnexecuteImpl()
{
	SwapSize();
}

void ResizeImageCommand::SwapSize()
{
	std::swap(m_widthRef, m_width);
	std::swap(m_heightRef, m_height);
}
