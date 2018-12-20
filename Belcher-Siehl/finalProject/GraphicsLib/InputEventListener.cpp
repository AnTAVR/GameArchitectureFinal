#include "InputEventListener.h"
#include "EventSystem.h"
#include "Event.h"
#include "KeyEvent.h"

// constructor for the InputEventListener class
InputEventListener::InputEventListener()
{
	getEventSystem()->addListener(KEY_PRESS_EVENT, this);
	getEventSystem()->addListener(MOUSE_CLICK_EVENT, this);
}

// destructor for the InputEventListener class
InputEventListener::~InputEventListener()
{

}

// determines which Event will fire off
void InputEventListener::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == KEY_PRESS_EVENT)
	{
		const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);

		if (keyEvent.getPressedKey() == ESCAPE_KEY)
		{
			getEventSystem()->fireEvent(EXIT_GAME_EVENT);
		}

		else if (keyEvent.getPressedKey() == ENTER_KEY)
		{
			getEventSystem()->fireEvent(CHANGE_ANIMATION_EVENT);
		}

		else if (keyEvent.getPressedKey() == SPACE_KEY)
		{
			getEventSystem()->fireEvent(PAUSE_UNITS_EVENT);
		}
	}

	else if (theEvent.getType() == MOUSE_CLICK_EVENT)
	{
		
	}
}