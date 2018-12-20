#include "InputTranslator.h"
#include "EventSystem.h"
#include "Event.h"
#include "KeyEvent.h"
#include "UpMoveEvent.h"
#include "DownMoveEvent.h"
#include "LeftMoveEvent.h"
#include "RightMoveEvent.h"
#include "StartLevelEvent.h"
#include "SelectButtonEvent.h"
#include "ExitGameEvent.h"


// constructor for the InputTranslator class
InputTranslator::InputTranslator(EventSystem* pEventSystem)
	: EventListener(pEventSystem)
{
	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the InputTranslator class
InputTranslator::~InputTranslator()
{
	cleanup();
}

// initializes the class object
int InputTranslator::init()
{
	if (!mIsInit)
	{
		// currently does not initialize anything

		mIsInit = true;
	}

	return 1;
}

// cleans up any remaining memory
void InputTranslator::cleanup()
{
	if (!mIsCleanup)
	{
		// currently has no data to clean up

		mIsCleanup = false;
	}
}

// handles the event
void InputTranslator::handleEvent(const Event& theEvent)
{
	// if the user pressed a key, perform the following:
	if (theEvent.getType() == KEY_PRESS_EVENT)
	{
		const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
	
		switch (keyEvent.getPressedKey())
		{

		case W_KEY:
			EventSystem::getInstance()->fireEvent(UpMoveEvent());
			break;

		case A_KEY:
			EventSystem::getInstance()->fireEvent(LeftMoveEvent());
			break;

		case S_KEY:
			EventSystem::getInstance()->fireEvent(DownMoveEvent());
			break;

		case D_KEY:
			EventSystem::getInstance()->fireEvent(RightMoveEvent());
			break;
		case UP_KEY:
			EventSystem::getInstance()->fireEvent(UpMoveEvent());
			break;

		case DOWN_KEY:
			EventSystem::getInstance()->fireEvent(DownMoveEvent());
			break;

		case LEFT_KEY:
			EventSystem::getInstance()->fireEvent(LeftMoveEvent());
			break;

		case RIGHT_KEY:
			EventSystem::getInstance()->fireEvent(RightMoveEvent());
			break;

		case SPACE_KEY:
			EventSystem::getInstance()->fireEvent(StartLevelEvent());
			break;

		case ENTER_KEY:
			EventSystem::getInstance()->fireEvent(SelectButtonEvent());
			break;

		case ESCAPE_KEY:
			EventSystem::getInstance()->fireEvent(ExitGameEvent());
			break;

		}
	}
}