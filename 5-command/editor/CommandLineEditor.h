#pragma once

#include <iostream>

#include "IDocument.h"
#include "ICommandFactory.h"
#include "CommandExecutionException.h"

constexpr auto POSITION_END = "end";

class CommandLineEditor
{
public:
	explicit CommandLineEditor(std::unique_ptr<IDocument>&& document);

	void OpenDocument(std::unique_ptr<IDocument>&& document);

	void InsertParagraph();

	void InsertImage();

	void SetTitle();

	void List();

	void ReplaceText();

	void ResizeImage();

	void DeleteItem();

	void Undo();

	void Redo();

	void Save();

private:
	std::unique_ptr<IDocument> m_document;

	std::optional<size_t> ParsePosition();
};
