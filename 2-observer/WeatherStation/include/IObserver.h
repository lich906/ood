#pragma once

template <typename T>
class IObservable;

/*
��������� ��������� IObserver. ��� ������ ������������� �����, 
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(const T& data) = 0;
	virtual ~IObserver() = default;
};
