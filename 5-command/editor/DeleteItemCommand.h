#pragma once

#include "Command.h"
#include "DocumentItem.h"

class DeleteItemCommand : public Command
{
public:
	DeleteItemCommand(IDocumentEditContext* document, size_t index, DocumentItem deletedItem);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

private:
	DocumentItem m_deletedItem;
	size_t m_index;
};
