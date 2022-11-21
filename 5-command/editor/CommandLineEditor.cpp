#include "CommandLineEditor.h"

CommandLineEditor::CommandLineEditor(std::unique_ptr<IDocument>&& document)
	: m_document(std::move(document))
{
}

void CommandLineEditor::OpenDocument(std::unique_ptr<IDocument>&& document)
{
	m_document = std::move(document);
}

void CommandLineEditor::InsertParagraph()
{
	auto position = ParsePosition();

	std::string text;
	std::getline(std::cin, text);

	m_document->InsertParagraph(text, position);
}

void CommandLineEditor::InsertImage()
{
	auto position = ParsePosition();
	
	std::filesystem::path path;
	int width, height;
	std::cin >> width >> height >> path;

	m_document->InsertImage(path, width, height, position);
}

void CommandLineEditor::SetTitle()
{
	std::string title;
	std::getline(std::cin, title);

	m_document->SetTitle(title);
}

void CommandLineEditor::List()
{
	std::cout << "Title: " << m_document->GetTitle() << std::endl;

	for (size_t index = 0; index < m_document->GetItemsCount(); ++index)
	{
		std::cout << index << ". ";
		auto item = m_document->GetItem(index);

		if (auto image = item.GetImage())
		{
			std::cout << "Image: " << image->GetWidth() << ' ' << image->GetHeight() << ' ' << image->GetPath() << std::endl;
		}
		else if (auto paragraph = item.GetParagraph())
		{
			std::cout << "Paragraph: " << paragraph->GetText() << std::endl;
		}
	}
}

void CommandLineEditor::ReplaceText()
{
	size_t index;
	std::cin >> index;
	std::string text;
	std::getline(std::cin, text);

	auto paragraph = m_document->GetItem(index).GetParagraph();

	if (paragraph == nullptr)
	{
		throw CommandExecutionException("Unable to replace paragraph text: item at position isn't a paragraph");
	}
	else
	{
		paragraph->SetText(text);
	}
}

void CommandLineEditor::ResizeImage()
{
	size_t index;
	std::cin >> index;
	int width, height;
	std::cin >> width >> height;

	auto image = m_document->GetItem(index).GetImage();

	if (image == nullptr)
	{
		throw CommandExecutionException("Unable to resize image: item at position isn't an image");
	}
	else
	{
		image->Resize(width, height);
	}
}

void CommandLineEditor::DeleteItem()
{
	size_t index;
	std::cin >> index;

	m_document->DeleteItem(index);
}

void CommandLineEditor::Undo()
{
	m_document->Undo();
}

void CommandLineEditor::Redo()
{
	m_document->Redo();
}

void CommandLineEditor::Save()
{
	std::filesystem::path path;
	std::cin >> path;

	m_document->Save(path);
}

std::optional<size_t> CommandLineEditor::ParsePosition()
{
	std::string positionStr;
	std::cin >> positionStr;

	if (positionStr == POSITION_END)
	{
		return std::nullopt;
	}

	return std::stoul(positionStr);
}
