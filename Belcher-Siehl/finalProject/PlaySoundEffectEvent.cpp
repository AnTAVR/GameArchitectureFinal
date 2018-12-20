#include "PlaySoundEffectEvent.h"

// constructor for the PlaySoundEffectEvent class
PlaySoundEffectEvent::PlaySoundEffectEvent(int sound)
	: Event(PLAY_SOUND_EFFECT_EVENT)
{
	mSound = sound;
}

// destructor for the PlaySoundEffectEvent class
PlaySoundEffectEvent::~PlaySoundEffectEvent()
{

}