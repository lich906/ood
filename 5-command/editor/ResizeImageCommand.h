#pragma once

#include "Command.h"

class ResizeImageCommand : public Command
{
public:
	ResizeImageCommand(IDocumentEditContext* document, size_t index, int width, int height, int oldWidth, int oldHeight);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	void ResizeImage(int width, int height) const;

	size_t m_index;
	int m_width, m_height, m_oldWidth, m_oldHeight;
};
