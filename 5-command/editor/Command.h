#pragma once

#include <memory>

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

	/*
	��������� �������� ��������, ����������� ��� ���������� ������ �������.
	*/
	virtual void Destroy() noexcept;

	virtual ~Command() = default;

protected:
	virtual void ExecuteImpl() = 0;
	virtual void UnexecuteImpl() = 0;

private:
	bool m_executed = false;
};
