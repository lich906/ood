#pragma once

#include "IDocument.h"
#include "IDocumentSaveStrategy.h"
#include "CommandHistory.h"
#include "Paragraph.h"
#include "Image.h"
#include "IDocumentEditContext.h"
#include "CommandExecutionException.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "DeleteItemCommand.h"
#include "SetTitleCommand.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"

class Document : public IDocument, private IDocumentEditContext
{
public:
	explicit Document(const std::shared_ptr<IDocumentSaveStrategy>& saveStrategy);

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override;

	std::shared_ptr<IImage> InsertImage(const std::filesystem::path& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override;

	void ReplaceParagraphText(size_t index, const std::string& text) override;

	void ResizeImage(size_t index, int width, int height) override;

	size_t GetItemsCount() const override;

	ConstDocumentItem GetItem(size_t index) const override;
	DocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	std::string GetTitle() const override;
	void SetTitle(const std::string& title) override;

	bool CanUndo() const override;
	void Undo() override;

	bool CanRedo() const override;
	void Redo() override;

	void Save(const std::filesystem::path& path) const;

private:
	const std::string DEFAULT_TITLE = "Untitled";

	std::shared_ptr<IParagraph> InsertParagraphEdit(const std::shared_ptr<IParagraph>& paragraph,
		std::optional<size_t> position = std::nullopt) override;

	std::shared_ptr<IImage> InsertImageEdit(const std::shared_ptr<IImage>& image,
		std::optional<size_t> position = std::nullopt) override;

	void DeleteItemEdit(size_t index) override;

	void SetTitleEdit(const std::string& title) override;

	void DeleteLastItemEdit() override;

	void RecoverDeletedItem(size_t index, const DocumentItem& item) override;

	DocumentItem& GetItemForEdit(size_t index) override;

	std::string m_title = DEFAULT_TITLE;
	std::vector<DocumentItem> m_items;
	CommandHistory m_commandHistory;
	std::shared_ptr<IDocumentSaveStrategy> m_documentSaveStrategy;
};
