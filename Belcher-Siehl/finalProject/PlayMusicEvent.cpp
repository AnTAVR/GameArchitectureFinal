#include "PlayMusicEvent.h"

// constructor for the PlayMusicEvent class
PlayMusicEvent::PlayMusicEvent(int music)
	: Event(PLAY_MUSIC_EVENT)
{
	mMusic = music;
}

// destructor for the PlayMusicEvent class
PlayMusicEvent::~PlayMusicEvent()
{

}