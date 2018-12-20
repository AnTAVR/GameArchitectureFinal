#pragma once

#include <Trackable.h>
#include "Font.h"
#include "Color.h"
#include "Vector2D.h"
#include "System.h"
#include "LevelManager.h"
#include "Button.h"
#include "Language.h"
#include "PermanentGameData.h"
#include "Animation.h"

#include <vector>
#include <string>

class GraphicsBuffer;

enum HUDButtons
{
	HEADS_UP_DISPLAY = -5,
	TOP_SCORE_DISPLAY = -4,
	BETWEEN_LEVELS_DISPLAY = -3,
	GAME_OVER_DISPLAY = -2,
	WIN_STATE_DISPLAY = -1,

	SCORE_TEXT = 0,
	SCORE_VALUE,
	COINS_VALUE,
	WORLD_TEXT,
	WORLD_VALUE,
	TIME_TEXT,
	TIME_VALUE
};

enum TopScoreButtons
{
	TOP_TEXT = 0,
	TOP_VALUE
};

enum BetweenLevelButtons
{
	WORLD_TEXT_CENTER = 0,
	WORLD_VALUE_CENTER,

	LIVES_VALUE
};

enum GameOverButtons
{
	GAME_OVER_TEXT = 0
};

enum WinStateButtons
{
	WIN_STATE_TEXT = 0
};

class HUD : public Trackable
{
public:
	HUD(std::string filename);
	~HUD();

	void init(Language* pLanguage);
	void cleanup();

	void drawHUD(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData);
	void drawHighScore(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData);
	void drawBetweenLevels(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData);
	void drawGameOver(System* pSystem, Language* pLanguage);
	void drawWinState(System* pSystem, Language* pLanguage);

	std::string setDisplay(int numPlaces, int passedValue);

	void calculateFrameRate(float frameRate);

	void addPoints(int points, int scoreMultiplier);

private:
	Font* mpFont;
	Color mColor;

	std::vector <Button*> mHUDButtonList;
	std::vector <Button*> mTopScoreButtonList;
	std::vector <Button*> mBetweenLevelsButtonList;
	std::vector <Button*> mGameOverButtonsList;
	std::vector <Button*> mWinStateButtonsList;

	std::string mDataFile;

	int mScore;
	int mFrameRate;

	int mScorePlacements;
	int mCoinPlacements;
	int mTimePlacements;

	int mIntendedFrameRate;
	int mFrameDivider;

	bool mIsInit;
	bool mIsCleanup;
};