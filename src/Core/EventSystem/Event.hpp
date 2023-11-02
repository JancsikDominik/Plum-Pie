#pragma once
#include <memory>

#include "EventManager.hpp"

namespace Plum
{
    class Observer;

    class Event 
    {
    public:
        using Ref = std::shared_ptr<Event>;

        virtual ~Event() = default;
    };

    class Observer 
    {
    public:
        using Ref = std::shared_ptr<Observer>;

        /**
         * \brief call this constructor or manually add the observer when creating a custom observer
         */
        Observer()
        {
            EventManager::AddObserver<decltype(this)>(this);
        }

        virtual ~Observer()
        {
            EventManager::RemoveObserver<decltype(this)>(this);
        }

        virtual void OnNotify(const Event* event) = 0;
    };

}
