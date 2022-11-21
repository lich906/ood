#pragma once

#include <memory>

#include "IDocumentEditContext.h"
#include "CommandExecutionException.h"

class Command
{
public:
	/*
	��������� ��������� ��������� ��� ���������� �������.
	�������� ����� ����������� ����� ExecuteImpl, ����������� ������ ��������. ExecuteImpl ������
	����������� ������-����������.
	*/
	void Execute();

	/*
	��������� ��������� ��������� ��� ������ �������.
	�������� ����� ����������� ����� UnexecuteImpl, ����������� ������ �������� ��� ������. UnexecuteImpl
	������ ����������� ������-����������.
	*/
	void Unexecute();

	virtual ~Command() = default;

protected:
	explicit Command(const std::shared_ptr<IDocumentEditContext>& documentEditContext);

	/*
	��������� �� ���������� �������
	*/
	std::shared_ptr<IDocumentEditContext> m_documentEditContext;

	virtual void ExecuteImpl() = 0;
	virtual void UnexecuteImpl() = 0;

private:
	bool m_executed = false;
};
