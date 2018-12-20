#pragma once

#include "System.h"
#include "GridManager.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GameObjectManager.h"

#include <Trackable.h>
#include <string>
#include <vector>

enum FrameData
{
	TIMER_FRAMES = 23
};

class Level : public Trackable
{
public:
	Level(System* pSystem, std::string filename, int levelNum);
	~Level();

	void init();
	void initLayout();
	void clear();

	void drawLevel();
	void decreaseTimer();

	void resetLevel();

	void setTimer(int difficulty) { mTimer = mTimerDifficultyList.at(difficulty); }
	void setTimerOnLoad(int timer) { mTimer = timer; }

	int getXPos(int i);
	int getYPos(int i);

	int getWorld() { return mWorld; };
	int getLevel() { return mLevel; };
	int getTimer() { return mTimer; };
	int getLevelType() { return mLevelType; }

	GridManager* getGridManager();
	GameObjectManager* getGameObjectManager() { return mpGameObjectManager; };

private:
	std::string mDataFile;
	std::string mLevelLayoutFile;

	System* mpSystem;
	GridManager* mpGridManager;

	GameObjectManager* mpGameObjectManager;

	GraphicsBuffer* mpBackground;

	Sprite* mpLevelSprite;
	std::vector<Sprite*> mLevelSpritesList;

	std::vector<int> mTimerDifficultyList;

	int mLevelNum;
	int mHeight;
	int mWidth;

	int mWorld;
	int mLevel;
	int mLevelType;

	int mTimer;
	int mTimerCounter;

	bool mIsInit;
	bool mIsLayoutInit;
	bool mIsClear;
};