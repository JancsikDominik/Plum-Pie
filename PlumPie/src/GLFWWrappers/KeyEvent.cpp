#include "KeyEvent.hpp"

namespace Plum
{
	KeyEvent::KeyEvent(Keyboard::Key key, Keyboard::Action action, uint32_t modifier)
		: key{ key }, action{ action }, modifier{ modifier }
	{
	}

	void KeyEvent::NotifyObservers()
	{
		EventManager::NotifyObservers<KeyEvent>(this);
	}



	KeyEventObserver::KeyEventObserver()
	{
		EventManager::AddObserver<KeyEvent>(this);
	}

	KeyEventObserver::~KeyEventObserver()
	{
		EventManager::RemoveObserver<KeyEvent>(this);
	}

	void KeyEventObserver::OnNotify(const Event* e)
	{
		const auto& keyEventPtr = dynamic_cast<const KeyEvent*>(e);
		PLUM_ASSERT(keyEventPtr != nullptr);
		OnKeyEvent(*keyEventPtr);
	}
}
