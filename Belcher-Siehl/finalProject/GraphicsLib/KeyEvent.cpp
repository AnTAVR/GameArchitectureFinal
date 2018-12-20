#include "KeyEvent.h"

// constructor for the KeyEvent class
KeyEvent::KeyEvent(int keyValue)
	: Event(KEY_PRESS_EVENT)
{
	mPressedKey = keyValue;
}

// destructor for the KeyEvent class
KeyEvent::~KeyEvent()
{

}

// returns the pressed key
int KeyEvent::getPressedKey() const
{
	return mPressedKey;
}