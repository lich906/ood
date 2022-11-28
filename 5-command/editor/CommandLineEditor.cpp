#include "CommandLineEditor.h"

static inline void ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

CommandLineEditor::CommandLineEditor(std::unique_ptr<IDocument>&& document, std::istream& input)
	: m_document(std::move(document))
	, m_input(input)
{
}

void CommandLineEditor::OpenDocument(std::unique_ptr<IDocument>&& document)
{
	m_document = std::move(document);
}

void CommandLineEditor::InsertParagraph()
{
	auto position = ParsePosition();

	std::string txt;
	std::getline(m_input, txt);
	ltrim(txt);

	m_document->InsertParagraph(txt, position);
}

void CommandLineEditor::InsertImage()
{
	auto position = ParsePosition();
	
	std::filesystem::path path;
	int width, height;
	m_input >> width >> height >> path;

	m_document->InsertImage(path, width, height, position);
}

void CommandLineEditor::SetTitle()
{
	std::string title;
	std::getline(m_input, title);
	ltrim(title);

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
	m_input >> index;
	std::string txt;
	std::getline(m_input, txt);
	ltrim(txt);

	if (auto paragraph = m_document->GetItem(index).GetParagraph())
	{
		paragraph->SetText(txt);
	}
	else
	{
		throw CommandExecutionException("Unable to change paragraph text: item at index isn't a paragraph");
	}
}

void CommandLineEditor::ResizeImage()
{
	size_t index;
	m_input >> index;
	int w, h;
	m_input >> w >> h;

	if (auto image = m_document->GetItem(index).GetImage())
	{
		image->Resize(w, h);
	}
	else
	{
		throw CommandExecutionException("Unable to resize image: item at index isn't an image");
	}
}

void CommandLineEditor::DeleteItem()
{
	size_t index;
	m_input >> index;

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
	m_input >> path;

	m_document->Save(path);
}

std::optional<size_t> CommandLineEditor::ParsePosition()
{
	std::string posStr;
	m_input >> posStr;

	if (posStr == POSITION_END)
	{
		return std::nullopt;
	}

	return std::stoul(posStr);
}
