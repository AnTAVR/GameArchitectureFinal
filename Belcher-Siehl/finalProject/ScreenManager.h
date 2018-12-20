#pragma once

#include <Trackable.h>
#include "Font.h"
#include "System.h"
#include "LevelManager.h"
#include "Button.h"
#include "Cursor.h"
#include "Language.h"
#include "HUD.h"

#include <vector>
#include <string>

class GraphicsBuffer;

enum ScreenType
{
	TITLE = 0,
	OPTIONS,
	BETWEEN_LEVELS,
	GAME_OVER,
	WIN_STATE,
	OPTIONS_SWITCHES = 99
};

class ScreenManager : public Trackable
{
public:
	ScreenManager(std::string filename);
	~ScreenManager();

	void init();
	void cleanup();

	void drawScreen(System* pSystem, LevelManager* pLevelManager, PermanentGameData* pPermanentGameData);
	void drawTitleScreen(System* pSystem, LevelManager* pLevelManager);

	void selectButton();
	void countdownToLevel();
	void countdownFromGameOver();
	void countdownFromWinState();

	void setScreenType(int screenType) { mScreenType = screenType; }
	void setCountdownTimer(int countdownTimer) { mCountdownTimer = countdownTimer; }

	Cursor* getCursor() { return mpCursor; }
	Language* getLanguage() { return mpLanguage; }
	Button* getOptionsSwitch(int index) { return mOptionsSwitchList.at(index); }
	int getOptionsSwitchSize() { return (int)mOptionsSwitchList.size(); }
	int getScreenType() { return mScreenType; }
	int getCountdownTimer() { return mCountdownTimer; }

private:
	std::string mDataFile;
	std::vector <GraphicsBuffer*> mGraphicsBufferList;
	std::vector <Button*> mTitleButtonList;
	std::vector <Button*> mOptionsButtonList;
	std::vector <Button*> mOptionsSwitchList;

	Cursor* mpCursor;
	Language* mpLanguage;
	HUD* mpHUD;

	int mScreenType;

	int mCountdownMax;
	int mCountdownGameOverMax;
	int mCountdownWinStateMax;
	int mCountdownTimer;

	bool mIsInit;
	bool mIsCleanup;
};