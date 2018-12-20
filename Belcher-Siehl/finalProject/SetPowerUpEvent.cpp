#include "SetPowerUpEvent.h"

// constructor for the PlayMusicEvent class
PowerUpEvent::PowerUpEvent(int powerVal)
	: Event(SET_POWER_UP_EVENT)
{
	mPower = powerVal;
}

// destructor for the PlayMusicEvent class
PowerUpEvent::~PowerUpEvent()
{

}