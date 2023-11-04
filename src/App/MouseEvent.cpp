#include "MouseEvent.hpp"
#include "Debugging/Debug.hpp"

namespace Plum
{

	MouseEvent::MouseEvent(Mouse::EventType type, Mouse::ButtonAction action, Mouse::Button button, uint32_t modifiers, glm::vec2 pos, glm::vec2 scrollOffset)
		: type{ type }, action{ action }, button{ button }, pos{ pos }, modifiers{ modifiers }, scrollOffset{ scrollOffset }
	{
	}

	MouseEvent::MouseEvent(Mouse::EventType type, glm::vec2 pos, Mouse::ButtonAction action, Mouse::Button button, uint32_t modifiers, glm::vec2 scrollOffset)
		: type{ type }, action{ action }, button{ button }, pos{ pos }, modifiers{ modifiers }, scrollOffset{ scrollOffset }
	{
	}

	void MouseEvent::NotifyObservers()
	{
		EventManager::NotifyObservers<MouseEvent>(this);
	}

	void MouseEventObserver::OnNotify(const Event* e)
	{
		const auto& mouseEvent = dynamic_cast<const MouseEvent*>(e);
		PLUM_ASSERT(mouseEvent != nullptr);
		OnMouseEvent(*mouseEvent);
	}
}

