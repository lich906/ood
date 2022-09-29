#pragma once
#include <map>
#include "IObservable.h"

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, const int priority = 0) override
	{
		RemoveObserver(observer);
		m_observers.insert(std::pair<int, ObserverType*>(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

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
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	bool m_observersLock = false;
	std::multimap<int, ObserverType*, std::greater<int>> m_observers;
};
