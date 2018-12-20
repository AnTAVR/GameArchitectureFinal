#pragma once

#include "Event.h"

class KeyEvent : public Event
{
public:
	// constructor and destructor
	KeyEvent(int keyValue);
	~KeyEvent();

	// accessors
	int getPressedKey() const;

private:
	int mPressedKey;
};