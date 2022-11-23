#pragma once

#include <iostream>

#include "IDocument.h"
#include "CommandExecutionException.h"

constexpr auto POSITION_END = "end";

class CommandLineEditor
{
public:
	CommandLineEditor(std::unique_ptr<IDocument>&& document, std::istream& input = std::cin);

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
	std::optional<size_t> ParsePosition();

	std::istream& m_input;
	std::unique_ptr<IDocument> m_document;
};
