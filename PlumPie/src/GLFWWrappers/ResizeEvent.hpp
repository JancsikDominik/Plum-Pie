#pragma once

#include "Core/EventSystem/Event.hpp"
#include "Core/EventSystem/EventManager.hpp"
#include "Debugging/Debug.hpp"

namespace Plum
{

	class ResizeEvent : public Event
	{
	public:
		ResizeEvent(const uint32_t width, const uint32_t height);

		void NotifyObservers();

		const uint32_t width;
		const uint32_t height;
	};


	class ResizeEventObserver : public Observer
	{
	public:
		virtual void OnResize(uint32_t width, uint32_t height) = 0;

	private:
		void OnNotify(const Event* e) override
		{
			const auto& resizeEvent = dynamic_cast<const ResizeEvent*>(e);
			PLUM_ASSERT(resizeEvent != nullptr);
			OnResize(resizeEvent->width, resizeEvent->height);
		}
	};
}