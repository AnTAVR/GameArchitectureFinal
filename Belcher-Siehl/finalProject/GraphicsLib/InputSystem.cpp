#include "InputSystem.h"
#include "EventSystem.h"
#include "Event.h"
#include "KeyEvent.h"

// constructor for the InputSystem class
InputSystem::InputSystem()
{
	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the InputSystem class
InputSystem::~InputSystem()
{
	cleanup();
}

// initializes the class object
void InputSystem::init()
{
	if (!mIsInit)
	{

		mIsInit = true;
	}
}

// cleans up the class object
void InputSystem::cleanup()
{
	if (!mIsCleanup)
	{

		mIsCleanup = true;
	}
}

// updates the class object based on if there is an input
void InputSystem::update(bool onLevel)
{

	if (onLevel)
	{
		SDL_PollEvent(&mEvent);
		if (mEvent.type == SDL_KEYDOWN || mEvent.type == SDL_KEYMAPCHANGED)
		{
			EventSystem::getInstance()->fireEvent(KeyEvent(mEvent.key.keysym.sym));
		}
		else if (mEvent.type == SDL_KEYUP)
		{
			EventSystem::getInstance()->fireEvent(KEY_UP_EVENT);
		}
	}
	else
	{
		while (SDL_PollEvent(&mEvent))
		{

			SDL_PollEvent(&mEvent);
			if (mEvent.type == SDL_KEYDOWN || mEvent.type == SDL_KEYMAPCHANGED)
			{
				EventSystem::getInstance()->fireEvent(KeyEvent(mEvent.key.keysym.sym));
			}
			else if (mEvent.type == SDL_KEYUP)
			{
				EventSystem::getInstance()->fireEvent(KEY_UP_EVENT);
			}
		}

	}
}