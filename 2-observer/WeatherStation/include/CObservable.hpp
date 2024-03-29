#pragma once
#include <map>
#include "IObservable.h"

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, const int priority = 0, const bool instantNotify = false) override
	{
		RemoveObserver(observer);
		m_observers.insert(std::pair<int, ObserverType*>(priority, &observer));

		if (instantNotify)
		{
			// ����� ���������� ������ ����������, ���� ���������� ���� instantNotify
			T data = GetChangedData(&T());
			observer.Update(data);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData(&T());

		auto observersCopy = m_observers;
		for (auto& observer : observersCopy)
		{
			(observer.second)->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observerToRemove) override
	{
		std::multimap<int, ObserverType*, std::greater<int>> updatedObservers;

		for (const auto& observer : m_observers)
		{
			if ((observer.second) != &observerToRemove)
			{
				updatedObservers.insert(observer);
			}
		}

		std::swap(updatedObservers, m_observers);
	}

protected:
	// ������-���������� ������ ����������� ������ �����,
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData(const T*) const = 0;

private:
	bool m_observersLock = false;
	std::multimap<int, ObserverType*, std::greater<int>> m_observers;
};
