#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(IDocumentEditContext* document, size_t index, DocumentItem deletedItem)
	: Command(document)
	, m_position(index)
	, m_deletedItem(std::move(deletedItem))
{
}

void DeleteItemCommand::ExecuteImpl()
{
	m_documentEditContext->DeleteItemEdit(m_position);
}

void DeleteItemCommand::UnexecuteImpl()
{
	// исправить команду при удалении картинки
	m_documentEditContext->RecoverDeletedItem(m_position, m_deletedItem);
}
