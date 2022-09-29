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
	virtual void Update(const T& data, const IObservable<T>* observablePtr) = 0;
	virtual ~IObserver() = default;
};
