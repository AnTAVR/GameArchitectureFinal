#pragma once

#include <Trackable.h>
#include "Grid.h"
#include "System.h"
#include "Level.h"

#include <vector>
#include <string>

// the LevelManager class
class LevelManager : public Trackable
{
public:
	// constructor and destructor
	LevelManager(std::string filename, System* pSystem);
	~LevelManager();

	// initializes and cleans up the class data
	void init();
	void cleanup();

	void initLevelLayout(int index);

	void nextLevel();
	void previousLevel();
	void firstLevel();

	void updateLevel();

	void accessOnLevel(int difficulty);
	void accessOnLevelOnLoad();
	void accessStart();
	void accessGameOver();

	void resetAllLevels();

	void setCurrentLevel(int level) { mCurrentLevel = level; }

	// accessors
	Level* getCurrentLevel();
	bool getOnLevel();
	bool getStart();
	bool getGameOver();
	bool getWin();
	int getCurrentLevelNumber();
	int getCurrentLevelOnLoad() { return mCurrentLevel; }
	int getSize() { return mLevelList.size(); }

private:
	System* mpSystem;

	std::vector <Level*> mLevelList;

	std::string mDataFile;
	int mTotalLevels;
	int mCurrentLevel;

	// information used to determine screen and grid size
	int mX;
	int mY;

	int mGridScaler;
	float mImageScaler;

	bool mOnLevel;
	bool mStart;
	bool mGameOver;
	bool mWin;

	bool mIsInit;
	bool mIsCleanup;
};