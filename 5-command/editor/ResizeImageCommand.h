#pragma once

#include "Command.h"

class ResizeImageCommand : public Command
{
public:
	ResizeImageCommand(IDocumentEditContext* document, size_t index, int width, int height, int oldWidth, int oldHeight);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	const int MIN_DIMENSION_SIZE = 1;
	const int MAX_DIMENSION_SIZE = 10000;

	void ResizeImage(int width, int height) const;

	size_t m_index;
	int m_width, m_height, m_oldWidth, m_oldHeight;
};
