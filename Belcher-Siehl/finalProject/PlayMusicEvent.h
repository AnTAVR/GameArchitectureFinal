#pragma once

#include "Event.h"

enum Music
{
	NO_MUSIC = -1,

	OVERWORLD = 0,
	OVERWORLD_FAST,

	UNDERGROUND,
	UNDERGROUND_FAST,

	DEATH,
	GAMEOVER,
	WORLD_CLEAR
};

class PlayMusicEvent : public Event
{
public:
	PlayMusicEvent(int music);
	~PlayMusicEvent();

	int getMusic() const { return mMusic; }

private:
	int mMusic;
};