#pragma once

#include "Core/EventSystem/Event.hpp"
#include "Core/EventSystem/EventManager.hpp"
#include "Debugging/Debug.hpp"

#include "Keyboard.hpp"

namespace Plum
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(Keyboard::Key key, Keyboard::Action action, uint32_t modifier);

		void NotifyObservers();

		const Keyboard::Key key;
		const Keyboard::Action action;
		const uint32_t modifier;
	};

	class KeyEventObserver : public Observer
	{
	public:
		KeyEventObserver();
		~KeyEventObserver();

		virtual void OnKeyEvent(const KeyEvent& keyevent) = 0;

	private:
		void OnNotify(const Event* e) override;
	};
}