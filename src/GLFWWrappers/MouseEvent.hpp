#pragma once

#include <glm/vec2.hpp>

#include "Core/EventSystem/Event.hpp"
#include "Core/EventSystem/EventManager.hpp"

#include "Mouse.hpp"

namespace Plum
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent(Mouse::EventType type, 
				   Mouse::ButtonAction action = Mouse::ButtonAction::Invalid, 
				   Mouse::Button button = Mouse::Button::Unknown,
				   uint32_t modifiers = 0,
				   glm::vec2 pos = {-1, -1},
				   glm::vec2 scrollOffset = {0, 0});

		MouseEvent(Mouse::EventType type,
			       glm::vec2 pos = { -1, -1 },
			       Mouse::ButtonAction action = Mouse::ButtonAction::Invalid,
			       Mouse::Button button = Mouse::Button::Unknown,
			       uint32_t modifiers = 0,
				   glm::vec2 scrollOffset = {0, 0});

		void NotifyObservers();

		const Mouse::EventType type;
		const Mouse::ButtonAction action;
		const Mouse::Button button;
		const glm::vec2 pos;
		const glm::vec2 scrollOffset;
		const uint32_t modifiers;
	};


	class MouseEventObserver : public Observer
	{
	public:
		virtual void OnMouseEvent(const MouseEvent& keyevent) = 0;

	private:
		void OnNotify(const Event* e) override;
	};
}


