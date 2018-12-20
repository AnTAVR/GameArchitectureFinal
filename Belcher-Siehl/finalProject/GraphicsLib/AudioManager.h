#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <Trackable.h>

#include <string>
#include <vector>

class AudioManager : public Trackable
{
public:
	AudioManager();
	~AudioManager();

	void init(std::string filename);
	void cleanup();

	void playMusic(int index);
	void playSoundEffects(int index);
	void haltMusic() { Mix_HaltMusic(); mLastMusic = -1; }

	void toggleSound();

	int getMusicSize() { return mNumMusic; }
	int getSoundEffectsSize() { return mNumSoundEffects; }
	int getLastMusic() { return mLastMusic; }

private:
	std::vector<Mix_Music*> mMusicList;
	std::vector<Mix_Chunk*> mSoundEffectList;

	int mNumMusic;
	int mNumSoundEffects;
	int mLastMusic;

	bool mIsMusicPlaying;
	bool mIsSoundPlaying;
	bool mSoundOn;

	bool mIsInit;
	bool mIsCleanup;
};