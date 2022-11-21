#pragma once

#include <memory>

#include "IDocumentEditContext.h"
#include "CommandExecutionException.h"

class Command
{
public:
	/*
	Реализует шаблонное поведение при выполнении команды.
	Вызывает чисто виртуальный метод ExecuteImpl, выполняющий нужное действие. ExecuteImpl должны
	перегрузить классы-наследники.
	*/
	void Execute();

	/*
	Реализует шаблонное поведение при отмене команды.
	Вызывает чисто виртуальный метод UnexecuteImpl, выполняющий нужное действие для отмены. UnexecuteImpl
	должны перегрузить классы-наследники.
	*/
	void Unexecute();

	virtual ~Command() = default;

protected:
	explicit Command(const std::shared_ptr<IDocumentEditContext>& documentEditContext);

	/*
	Указатель на получателя команды
	*/
	std::shared_ptr<IDocumentEditContext> m_documentEditContext;

	virtual void ExecuteImpl() = 0;
	virtual void UnexecuteImpl() = 0;

private:
	bool m_executed = false;
};
