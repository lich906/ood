#pragma once

#include "Command.h"

class ResizeImageCommand : public Command
{
public:
	ResizeImageCommand(int& widthRef, int& heightRef, int width, int height);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	void SwapSize();

	int& m_widthRef, & m_heightRef;
	int m_width, m_height;
};
