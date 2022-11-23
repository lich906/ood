#include "Document.h"

Document::Document(const std::shared_ptr<IDocumentSaveStrategy>& saveStrategy)
	: m_documentSaveStrategy(saveStrategy)
{
}

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	std::shared_ptr<IParagraph> paragraph = std::make_shared<Paragraph>(text);
	std::unique_ptr<Command> command = std::make_unique<InsertParagraphCommand>(static_cast<IDocumentEditContext*>(this), paragraph, position);
	command->Execute();
	m_commandHistory.AddCommand(std::move(command));

	return paragraph;
}

std::shared_ptr<IImage> Document::InsertImage(const std::filesystem::path& path, int width, int height, std::optional<size_t> position)
{
	std::shared_ptr<IImage> image = std::make_shared<Image>(path, width, height);
	std::unique_ptr<Command> command = std::make_unique<InsertImageCommand>(static_cast<IDocumentEditContext*>(this), image, position);
	command->Execute();
	m_commandHistory.AddCommand(std::move(command));

	return image;
}

void Document::ReplaceParagraphText(size_t index, const std::string& text)
{
	if (auto paragraph = GetItem(index).GetParagraph())
	{
		std::unique_ptr<Command> command = std::make_unique<ReplaceTextCommand>(static_cast<IDocumentEditContext*>(this), index,
			text, paragraph->GetText());
		command->Execute();
		m_commandHistory.AddCommand(std::move(command));
	}
	else
	{
		throw CommandExecutionException("Unable to replace paragraph text: item at position isn't a paragraph");
	}
}

void Document::ResizeImage(size_t index, int width, int height)
{
	if (auto image = GetItem(index).GetImage())
	{
		std::unique_ptr<Command> command = std::make_unique<ResizeImageCommand>(static_cast<IDocumentEditContext*>(this),
			index, width, height, image->GetWidth(), image->GetWidth());
		command->Execute();
		m_commandHistory.AddCommand(std::move(command));
	}
	else
	{
		throw CommandExecutionException("Unable to replace paragraph text: item at position isn't a paragraph");
	}
}

void Document::DeleteItem(size_t index)
{
	std::unique_ptr<Command> command = std::make_unique<DeleteItemCommand>(static_cast<IDocumentEditContext*>(this), index, m_items[index]);
	command->Execute();
	m_commandHistory.AddCommand(std::move(command));
}

std::string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const std::string& title)
{
	std::unique_ptr<Command> command = std::make_unique<SetTitleCommand>(static_cast<IDocumentEditContext*>(this), title, m_title);
	command->Execute();
	m_commandHistory.AddCommand(std::move(command));
}

bool Document::CanUndo() const
{
	return m_commandHistory.CanUndo();
}

void Document::Undo()
{
	m_commandHistory.Undo();
}

bool Document::CanRedo() const
{
	return m_commandHistory.CanRedo();
}

void Document::Redo()
{
	m_commandHistory.Redo();
}

void Document::Save(const std::filesystem::path& path) const
{
	m_documentSaveStrategy->Save(path, this);
}

std::shared_ptr<IParagraph> Document::InsertParagraphEdit(const std::shared_ptr<IParagraph>& paragraph, std::optional<size_t> position)
{
	if (!position.has_value())
	{
		m_items.push_back(paragraph);
	}
	else if (position <= m_items.size())
	{
		m_items.insert(m_items.begin() + *position, paragraph);
	}
	else
	{
		throw CommandExecutionException("Failed to insert paragraph: invalid position");
	}

	return paragraph;
}

std::shared_ptr<IImage> Document::InsertImageEdit(const std::shared_ptr<IImage>& image, std::optional<size_t> position)
{
	if (!position.has_value())
	{
		m_items.push_back(image);
	}
	else if (position <= m_items.size())
	{
		m_items.insert(m_items.begin() + *position, image);
	}
	else
	{
		throw CommandExecutionException("Failed to insert image: invalid position");
	}

	return image;
}

void Document::DeleteItemEdit(size_t index)
{
	if (index >= m_items.size())
	{
		throw CommandExecutionException("Failed to delete item: invalid position");
	}

	m_items.erase(m_items.begin() + index);
}

void Document::SetTitleEdit(const std::string& title)
{
	m_title = title;
}

void Document::DeleteLastItemEdit()
{
	DeleteItemEdit(m_items.size() - 1);
}

void Document::RecoverDeletedItem(size_t index, const DocumentItem& item)
{
	m_items.insert(m_items.begin() + index, item);
}

DocumentItem& Document::GetItemForEdit(size_t index)
{
	if (index >= m_items.size())
	{
		throw CommandExecutionException("Failed to edit item: invalid position");
	}

	return m_items[index];
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

ConstDocumentItem Document::GetItem(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Unable to get item: index is out of range");
	}

	return m_items[index];
}

DocumentItem Document::GetItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Unable to get item: index is out of range");
	}

	return m_items[index];
}
