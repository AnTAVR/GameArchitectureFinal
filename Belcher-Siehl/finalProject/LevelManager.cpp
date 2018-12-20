#include "LevelManager.h"
#include "EventSystem.h"
#include "WinGameEvent.h"

#include <fstream>

using namespace std;

// constructor for the LevelManager class
LevelManager::LevelManager(string filename, System* pSystem)
{
	mDataFile = filename;
	mpSystem = pSystem;

	mIsInit = false;
	mIsCleanup = false;

	mOnLevel = false;
	mStart = true;
	mGameOver = false;
	mWin = false;

	mCurrentLevel = 0;
}

// destructor for the LevelManager class
LevelManager::~LevelManager()
{
	cleanup();
}

// initializes the LevelManager class's Grid
void LevelManager::init()
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		const string TOTAL_LEVELS = "TOTAL LEVELS";

		fin.open(mDataFile);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(TOTAL_LEVELS);
			if (pos != string::npos)
			{
				fin >> mTotalLevels;
			}
		}

		fin.clear();
		fin.close();
		
		// creates and initializes each level as specified in the data file
		for (int i = 1; i <= mTotalLevels; i++)
		{
			mLevelList.push_back(new Level(mpSystem, mDataFile, i));
		}

		for (unsigned i = 0; i < mLevelList.size(); i++)
		{
			mLevelList.at(i)->init();
		}
	}
}

// cleans up all remaining data
void LevelManager::cleanup()
{
	if (!mIsCleanup)
	{
		for (unsigned i = 0; i < mLevelList.size(); i++)
		{
			delete mLevelList.at(i);
		}

		mIsCleanup = true;
	}
}

// initializes a specific level
void LevelManager::initLevelLayout(int index)
{
	mLevelList.at(index)->initLayout();
}

// updates information pertaining to the current Level object
void LevelManager::updateLevel()
{
	mLevelList.at(mCurrentLevel)->drawLevel();
	mLevelList.at(mCurrentLevel)->decreaseTimer();
}

// moves to the next level
void LevelManager::nextLevel()
{
	mOnLevel = false;

	if ((unsigned)mCurrentLevel < mLevelList.size() - 1)
	{
		mCurrentLevel++;
	}

	else
	{
		EventSystem::getInstance()->fireEvent(WinGameEvent());
	}
}

// returns to the previous level
void LevelManager::previousLevel()
{
	if (mCurrentLevel > 0)
	{
		mCurrentLevel--;
		mOnLevel = false;
	}
}

// returns to the first level
void LevelManager::firstLevel()
{
	mCurrentLevel = 0;
	mOnLevel = false;
}

// changes accessibility for the next level
void LevelManager::accessOnLevel(int difficulty)
{
	mLevelList.at(mCurrentLevel)->setTimer(difficulty);
	mOnLevel = !mOnLevel;
}

// changes accessibility for the next level
void LevelManager::accessOnLevelOnLoad()
{
	mOnLevel = true;
}

// makes it so that the player can no longer return to the start screen
void LevelManager::accessStart()
{
	if (mStart)
	{
		mStart = false;
	}
}

// forces a game over
void LevelManager::accessGameOver()
{
	mGameOver = true;
	mOnLevel = false;
}

// resets every level in the manager
void LevelManager::resetAllLevels()
{
	for (unsigned i = 0; i < mLevelList.size(); i++)
	{
		mLevelList.at(i)->resetLevel();
	}
}

// returns the current level
Level* LevelManager::getCurrentLevel()
{
	return mLevelList.at(mCurrentLevel);
}

// returns whether or not the level is currently available
bool LevelManager::getOnLevel()
{
	return mOnLevel;
}

// returns whether or not the player is on the title screen
bool LevelManager::getStart()
{
	return mStart;
}

// returns whether or not the player has lost
bool LevelManager::getGameOver()
{
	return mGameOver;
}

// returns whether or not the player has won
bool LevelManager::getWin()
{
	return mWin;
}

// returns the number of the current level
int LevelManager::getCurrentLevelNumber()
{
	return mCurrentLevel + 1;
}