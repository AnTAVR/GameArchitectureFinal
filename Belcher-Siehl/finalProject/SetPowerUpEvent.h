#pragma once
#include "Event.h"

class PowerUpEvent : public Event
{
public:
	PowerUpEvent(int powerVal);
	~PowerUpEvent();

	int getPower() const { return mPower; }

private:
	int mPower;
};