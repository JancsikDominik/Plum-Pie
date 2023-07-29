#pragma once
#include <memory>

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

        virtual ~Observer() = default;
        virtual void OnNotify(const Event* event) = 0;
    };

}