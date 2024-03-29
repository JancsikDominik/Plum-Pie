#ifndef PLUMPIE_EVENT_MANAGER_HPP
#define PLUMPIE_EVENT_MANAGER_HPP

#include <unordered_map>
#include <vector>
#include <typeindex>

namespace Plum
{
	class Observer;

	class EventManager 
    {
    public:
        static EventManager& GetInstance() 
        {
            static EventManager instance;
            return instance;
        }

        template <typename EventType>
        static void AddObserver(Observer* observer) 
        {
            GetInstance().AddObserverImpl<EventType>(observer);
        }

        template <typename EventType>
        static void RemoveObserver(Observer* observer) 
        {
            GetInstance().RemoveObserverImpl<EventType>(observer);
        }

        template <typename EventType>
        static void NotifyObservers(const EventType* event) 
        {
            GetInstance().NotifyObserversImpl<EventType>(event);
        }

    private:
        std::unordered_map<std::type_index, std::vector<Observer*>> observers;

        template <typename EventType>
        void AddObserverImpl(Observer* observer) 
        {
            observers[typeid(EventType)].push_back(observer);
        }

        template <typename EventType>
        void RemoveObserverImpl(Observer* observer) 
        {
            auto& observerList = observers[typeid(EventType)];
            const auto it = std::ranges::find(observerList, observer);
            if (it != observerList.end()) 
            {
                observerList.erase(it);
            }
        }

        template <typename EventType>
        void NotifyObserversImpl(const EventType* event) 
        {
	        const auto& observerList = observers[typeid(EventType)];
            for (Observer* observer : observerList) 
            {
                observer->OnNotify(event);
            }
        }
    };
}


#endif