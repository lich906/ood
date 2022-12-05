#include "Document.h"

Document::Document(const std::shared_ptr<IDocumentSaveStrategy>& saveStrategy)
	: m_documentSaveStrategy(saveStrategy)
{
}

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	std::shared_ptr<IParagraph> paragraph = std::make_shared<Paragraph>(text, [this](std::unique_ptr<Command>&& cmd) {
		SaveCommandToHistory(std::move(cmd));
	});

	std::unique_ptr<Command> command = std::make_unique<InsertParagraphCommand>(
		[this, paragraph, position]() {
			InsertParagraphEdit(paragraph, position);
		},
		[this, position]() {
			if (position.has_value())
			{
				DeleteItemEdit(*position);
			}
			else
			{
				DeleteLastItemEdit();
			}
		}
	);

	command->Execute();
	SaveCommandToHistory(std::move(command));

	return paragraph;
}

std::shared_ptr<IImage> Document::InsertImage(const std::filesystem::path& path, int width, int height, std::optional<size_t> position)
{
	auto commandSaver = [this](std::unique_ptr<Command>&& cmd) {
		SaveCommandToHistory(std::move(cmd));
	};

	std::shared_ptr<IImage> image = std::make_shared<Image>(path, width, height, commandSaver);

	std::unique_ptr<Command> command = std::make_unique<InsertImageCommand>(image,
		[this, position](const std::shared_ptr<IImage>& img) {
			InsertImageEdit(img, position);
		},
		[this, position]() {
			if (position.has_value())
			{
				DeleteItemEdit(*position);
			}
			else
			{
				DeleteLastItemEdit();
			}
		}, commandSaver);

	command->Execute();
	m_commandHistory.AddCommand(std::move(command));

	return image;
}

void Document::DeleteItem(size_t index)
{
	auto deletedItem = m_items.at(index);
	std::unique_ptr<Command> command = std::make_unique<DeleteItemCommand>(
		[this, index]() {
			DeleteItemEdit(index);
		},
		[this, index, deletedItem]() {
			InsertDocumentItem(index, deletedItem);
		}
	);

	command->Execute();
	m_commandHistory.AddCommand(std::move(command));
}

std::string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const std::string& title)
{
	std::unique_ptr<Command> command = std::make_unique<SetTitleCommand>(
		[this, title]() {
			m_title = title;
		},
		[this, title = m_title]() {
			m_title = title;
		}
	);

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

void Document::SaveCommandToHistory(std::unique_ptr<Command>&& command)
{
	m_commandHistory.AddCommand(std::forward<std::unique_ptr<Command>>(command));
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

void Document::DeleteLastItemEdit()
{
	DeleteItemEdit(m_items.size() - 1);
}

void Document::InsertDocumentItem(size_t index, const DocumentItem& item)
{
	m_items.insert(m_items.begin() + index, item);
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

size_t Document::GetIndex(std::optional<size_t> position) const
{
	if (position.has_value())
	{
		return *position;
	}
	else
	{
		return m_items.size();
	}
}
