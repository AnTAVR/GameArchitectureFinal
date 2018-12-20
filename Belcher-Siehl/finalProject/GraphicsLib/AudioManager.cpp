#include "AudioManager.h"

#include <fstream>

using namespace std;

// constructor for the AudioManager class
AudioManager::AudioManager()
{
	mIsInit = false;
	mIsCleanup = false;
	mIsMusicPlaying = false;
	mIsSoundPlaying = false;
	mSoundOn = true;

	mLastMusic = -1;
}

// destructor for the AudioManager class
AudioManager::~AudioManager()
{
	cleanup();
}

// initializes the AudioManager class
void AudioManager::init(string filename)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		string tempString;

		const string NUM_MUSIC = "NUM MUSIC";
		const string OVERWORLD_THEME = "OVERWORLD THEME";
		const string OVERWORLD_FAST_THEME = "OVERWORLD FAST THEME";
		const string UNDERGROUND_THEME = "UNDERGROUND THEME";
		const string UNDERGROUND_FAST_THEME = "UNDERGROUND FAST THEME";
		const string DEATH_THEME = "DEATH THEME";
		const string GAMEOVER_THEME = "GAMEOVER THEME";
		const string WORLD_CLEAR_THEME = "WORLD CLEAR THEME";

		const string NUM_SOUND_EFFECTS = "NUM SOUND EFFECTS";
		const string PAUSE_SOUND = "PAUSE SOUND";
		const string JUMP_SMALL_SOUND = "JUMP SMALL SOUND";
		const string STOMP_SOUND = "STOMP SOUND";
		const string BREAK_BLOCK_SOUND = "BREAK BLOCK SOUND";
		const string FLAGPOLE_SOUND = "FLAGPOLE SOUND";
		const string COIN_SOUND = "COIN SOUND";
		const string ONE_UP_SOUND = "1-UP SOUND";

		fin.open(filename);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			// obtains music data from the file
			pos = line.find(NUM_MUSIC);
			if (pos != string::npos)
			{
				fin >> mNumMusic;
			}

			pos = line.find(OVERWORLD_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(OVERWORLD_FAST_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(UNDERGROUND_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(UNDERGROUND_FAST_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(DEATH_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(GAMEOVER_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			pos = line.find(WORLD_CLEAR_THEME);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Music* pTempSound = Mix_LoadMUS(tempString.c_str());
				mMusicList.push_back(pTempSound);
			}

			// obtains sound effect data from the data file
			pos = line.find(NUM_SOUND_EFFECTS);
			if (pos != string::npos)
			{
				fin >> mNumSoundEffects;
			}

			pos = line.find(PAUSE_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(JUMP_SMALL_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(STOMP_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(BREAK_BLOCK_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(FLAGPOLE_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(COIN_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}

			pos = line.find(ONE_UP_SOUND);
			if (pos != string::npos)
			{
				fin >> tempString;
				Mix_Chunk* pTempSound = Mix_LoadWAV(tempString.c_str());
				mSoundEffectList.push_back(pTempSound);
			}
		}

		fin.clear();
		fin.close();

		mIsInit = true;
	}
}

// clears the AudioManager class
void AudioManager::cleanup()
{
	if (!mIsCleanup)
	{
		for (int i = 0; i < mNumMusic; i++)
		{
			Mix_FreeMusic(mMusicList.at(i));
		}

		for (int i = 0; i < mNumSoundEffects; i++)
		{
			Mix_FreeChunk(mSoundEffectList.at(i));
		}

		Mix_Quit();
		SDL_Quit();

		mIsCleanup = true;
	}
}

// plays a designated song
void AudioManager::playMusic(int index)
{
	if (Mix_PlayingMusic() && mLastMusic != index)
	{
		Mix_HaltMusic();
	}
	
	if (mLastMusic != index)
	{
		// plays "scene" music, which loops indefinitely
		if (index >= 0 && index <= 1)
		{
			Mix_PlayMusic(mMusicList.at(index), -1);
		}
	
		// plays "event" music, which does not loop
		else
		{
			Mix_PlayMusic(mMusicList.at(index), 0);
		}
	
		mLastMusic = index;
	}
}

// plays a designated sound effect
void AudioManager::playSoundEffects(int index)
{
	if (Mix_Playing(0))
	{
		Mix_HaltChannel(0);
	}
	
	Mix_PlayChannel(0, mSoundEffectList.at(index), 0);
}

// change the volume for everything
void AudioManager::toggleSound()
{
	if (mSoundOn)
	{
		Mix_Volume(-1, 0);
		Mix_VolumeMusic(0);
		mSoundOn = false;
	}

	else
	{
		Mix_Volume(-1, 128);
		Mix_VolumeMusic(128);
		mSoundOn = true;
	}
}