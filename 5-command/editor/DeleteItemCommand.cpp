#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(IDocumentEditContext* document, size_t index, DocumentItem deletedItem)
	: Command(document)
	, m_index(index)
	, m_deletedItem(std::move(deletedItem))
{
}

void DeleteItemCommand::ExecuteImpl()
{
	m_documentEditContext->DeleteItemEdit(m_index);
}

void DeleteItemCommand::UnexecuteImpl()
{
	m_documentEditContext->RecoverDeletedItem(m_index, m_deletedItem);
}
