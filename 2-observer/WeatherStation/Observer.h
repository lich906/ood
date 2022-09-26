#pragma once

#include <map>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(const T& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, const int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

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

		m_observersLock = true;
		for (auto& observer : m_observers)
		{
			(observer.second)->Update(data);
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
