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
		m_observers.insert(std::pair<int, ObserverType*>(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		m_observersLock = true;
		for (auto& observer : m_observers)
		{
			(observer.second)->Update(data, this);
		}
		m_observersLock = false;
	}

	void RemoveObserver(ObserverType& observerToRemove) override
	{
		if (!m_observersLock)
		{
			std::multimap<int, ObserverType*, std::greater<int>> observersCopy;

			for (const auto& observer : m_observers)
			{
				if ((observer.second) != &observerToRemove)
				{
					observersCopy.insert(observer);
				}
			}

			std::swap(observersCopy, m_observers);
		}
		else
		{
			m_observersLock = false;
			throw std::logic_error("Cannnot delete observer during notifying process");
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	bool m_observersLock = false;
	std::multimap<int, ObserverType*, std::greater<int>> m_observers;
};
