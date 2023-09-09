#include "ResizeEvent.hpp"

Plum::ResizeEvent::ResizeEvent(const uint32_t width, const uint32_t height)
	:width{ width }, height{ height }
{
}

void Plum::ResizeEvent::NotifyObservers()
{
	EventManager::NotifyObservers<ResizeEvent>(this);
}
