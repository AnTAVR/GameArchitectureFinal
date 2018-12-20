#pragma once

#pragma once
#include "Event.h"

enum SoundEffects
{
	PAUSE = 0,
	JUMP_SMALL,
	STOMP,
	BREAK_BLOCK,
	FLAGPOLE,
	EARN_COIN,
	ONE_UP
};

class PlaySoundEffectEvent : public Event
{
public:
	PlaySoundEffectEvent(int sound);
	~PlaySoundEffectEvent();

	int getSound() const { return mSound; }

private:
	int mSound;
};