#include "ScreenManager.h"
#include "GraphicsBuffer.h"

#include "EventSystem.h"
#include "ExitGameEvent.h"
#include "StartLevelEvent.h"
#include "StartLevelGameplayEvent.h"
#include "ChangeDifficultyEvent.h"
#include "LoadGameEvent.h"
#include "PlaySoundEffectEvent.h"
#include "PlayMusicEvent.h"
#include "ToggleAudioEvent.h"

#include "Game.h"

#include <fstream>

using namespace std;

// constructor for the ScreenManager class
ScreenManager::ScreenManager(string filename)
{
	mDataFile = filename;

	mIsInit = false;
	mIsCleanup = false;

	mCountdownTimer = 0;
}

// destructor for the ScreenManager class
ScreenManager::~ScreenManager()
{
	cleanup();
}

// initializes the ScreenManager class's variables
void ScreenManager::init()
{
	if (!mIsInit)
	{
		mpCursor = new Cursor();
		mpCursor->init(mDataFile);

		mpLanguage = new Language();
		mpLanguage->init(mDataFile);

		mpHUD = new HUD(mDataFile);
		mpHUD->init(mpLanguage);

		ifstream fin;
		size_t pos;
		string line;

		string tempString;

		int numTitleButtons, numOptionsButtons, numOptionsSwitchesButtons;

		const string TITLE_SCREEN = "TITLE SCREEN";
		const string OPTIONS_SCREEN = "OPTIONS SCREEN";
		const string BETWEEN_LEVELS_SCREEN = "BETWEEN LEVELS SCREEN";
		const string GAME_OVER_SCREEN = "GAME OVER SCREEN";
		const string WIN_STATE_SCREEN = "WIN STATE SCREEN";
		const string BETWEEN_LEVELS_COUNTDOWN_TIMER = "BETWEEN LEVELS COUNTDOWN TIMER";
		const string GAME_OVER_COUNTDOWN_TIMER = "GAME OVER COUNTDOWN TIMER";
		const string WIN_STATE_COUNTDOWN_TIMER = "WIN STATE COUNTDOWN TIMER";
		const string NUM_TITLE_BUTTONS = "NUM TITLE BUTTONS";
		const string NUM_OPTIONS_BUTTONS = "NUM OPTIONS BUTTONS";
		const string NUM_OPTIONS_SWITCHES_BUTTONS = "NUM OPTIONS SWITCHES BUTTONS";

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
		
			pos = line.find(TITLE_SCREEN);
			if (pos != string::npos)
			{
				fin >> tempString;
				GraphicsBuffer* temp = new GraphicsBuffer(tempString, false);

				mGraphicsBufferList.push_back(temp);
			}

			pos = line.find(OPTIONS_SCREEN);
			if (pos != string::npos)
			{
				fin >> tempString;
				GraphicsBuffer* temp = new GraphicsBuffer(tempString, false);

				mGraphicsBufferList.push_back(temp);
			}

			pos = line.find(BETWEEN_LEVELS_COUNTDOWN_TIMER);
			if (pos != string::npos)
			{
				fin >> mCountdownMax;
			}

			pos = line.find(GAME_OVER_COUNTDOWN_TIMER);
			if (pos != string::npos)
			{
				fin >> mCountdownGameOverMax;
			}

			pos = line.find(WIN_STATE_COUNTDOWN_TIMER);
			if (pos != string::npos)
			{
				fin >> mCountdownWinStateMax;
			}

			pos = line.find(BETWEEN_LEVELS_SCREEN);
			if (pos != string::npos)
			{
				fin >> tempString;
				GraphicsBuffer* temp = new GraphicsBuffer(tempString, false);

				mGraphicsBufferList.push_back(temp);
			}

			pos = line.find(GAME_OVER_SCREEN);
			if (pos != string::npos)
			{
				fin >> tempString;
				GraphicsBuffer* temp = new GraphicsBuffer(tempString, false);

				mGraphicsBufferList.push_back(temp);
			}

			pos = line.find(WIN_STATE_SCREEN);
			if (pos != string::npos)
			{
				fin >> tempString;
				GraphicsBuffer* temp = new GraphicsBuffer(tempString, false);

				mGraphicsBufferList.push_back(temp);
			}

			pos = line.find(NUM_TITLE_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numTitleButtons;
			}

			pos = line.find(NUM_OPTIONS_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numOptionsButtons;
			}

			pos = line.find(NUM_OPTIONS_SWITCHES_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numOptionsSwitchesButtons;
			}

		}

		fin.clear();
		fin.close();

		for (int i = 0; i < numTitleButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mTitleButtonList.push_back(pTempButton);
			mTitleButtonList.at(i)->init(mDataFile, TITLE, mpLanguage->getNumLanguages());
		}

		for (int i = 0; i < numOptionsButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mOptionsButtonList.push_back(pTempButton);
			mOptionsButtonList.at(i)->init(mDataFile, OPTIONS, mpLanguage->getNumLanguages());
		}

		for (int i = 0; i < numOptionsSwitchesButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mOptionsSwitchList.push_back(pTempButton);
			mOptionsSwitchList.at(i)->init(mDataFile, OPTIONS_SWITCHES, mpLanguage->getNumLanguages());
		}

		mIsInit = true;
	}
}

// cleans up memory
void ScreenManager::cleanup()
{
	if (!mIsCleanup)
	{
		for (unsigned i = 0; i < mGraphicsBufferList.size(); i++)
		{
			delete mGraphicsBufferList.at(i);
		}
		mGraphicsBufferList.clear();

		for (unsigned i = 0; i < mTitleButtonList.size(); i++)
		{
			delete mTitleButtonList.at(i);
		}
		mTitleButtonList.clear();

		for (unsigned i = 0; i < mOptionsButtonList.size(); i++)
		{
			delete mOptionsButtonList.at(i);
		}
		mOptionsButtonList.clear();

		for (unsigned i = 0; i < mOptionsSwitchList.size(); i++)
		{
			delete mOptionsSwitchList.at(i);
		}
		mOptionsSwitchList.clear();

		delete mpCursor;
		delete mpLanguage;
		delete mpHUD;

		mIsCleanup = true;
	}
}

void ScreenManager::drawScreen(System* pSystem, LevelManager* pLevelManager, PermanentGameData* pPermanentGameData)
{
	if (!pLevelManager->getOnLevel())
	{
		drawTitleScreen(pSystem, pLevelManager);

		if (mScreenType == TITLE || mScreenType == OPTIONS)
		{
			mpHUD->drawHighScore(pSystem, pLevelManager, mpLanguage, pPermanentGameData);
			pSystem->getAudioManager()->playMusic(OVERWORLD);
		}

		else if (mScreenType == BETWEEN_LEVELS)
		{
			mpHUD->drawBetweenLevels(pSystem, pLevelManager, mpLanguage, pPermanentGameData);
			countdownToLevel();
		}

		else if (mScreenType == GAME_OVER)
		{
			mpHUD->drawGameOver(pSystem, mpLanguage);
			countdownFromGameOver();
		}

		else if (mScreenType == WIN_STATE)
		{
			mpHUD->drawWinState(pSystem, mpLanguage);
			countdownFromWinState();
		}
	}

	mpHUD->drawHUD(pSystem, pLevelManager, mpLanguage, pPermanentGameData);
}

// draws the chosen data file
void ScreenManager::drawTitleScreen(System* pSystem, LevelManager* pLevelManager)
{
	Sprite* pTemp = new Sprite(mGraphicsBufferList.at(mScreenType), DEFAULT_X, DEFAULT_Y, mGraphicsBufferList.at(mScreenType)->getWidth(), mGraphicsBufferList.at(mScreenType)->getHeight());
	pSystem->getGraphics()->draw(DEFAULT_X, DEFAULT_Y, pTemp, pLevelManager->getCurrentLevel()->getGridManager()->getImageScale(), true);

	// draws various aspects of the title screen, including buttons and the cursor
	if (mScreenType == TITLE)
	{
		for (unsigned i = 0; i < mTitleButtonList.size(); i++)
		{
			mTitleButtonList.at(i)->drawButton(pSystem, mpLanguage->getLanguage());
		}

		mpCursor->drawCursor(pSystem, mTitleButtonList.at(mpCursor->getSelectedButton())->getLocX(), mTitleButtonList.at(mpCursor->getSelectedButton())->getLocY());
	}

	else if (mScreenType == OPTIONS)
	{
		for (unsigned i = 0; i < mOptionsButtonList.size(); i++)
		{
			mOptionsButtonList.at(i)->drawButton(pSystem, mpLanguage->getLanguage());
		}

		for (unsigned i = 0; i < mOptionsSwitchList.size(); i++)
		{
			mOptionsSwitchList.at(i)->drawButton(pSystem, mpLanguage->getLanguage());
		}

		mpCursor->drawCursor(pSystem, mOptionsButtonList.at(mpCursor->getSelectedButton())->getLocX(), mOptionsButtonList.at(mpCursor->getSelectedButton())->getLocY());
	}

	delete pTemp;
}

// Makes a decision based on a button the user selects
void ScreenManager::selectButton()
{
	EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(PAUSE));

	switch (mpCursor->getSelectedButton())
	{
	case BUTTON_PLAY_DIFFICULTY:
		if (mScreenType == TITLE)
		{
			EventSystem::getInstance()->fireEvent(StartLevelEvent());
		}

		else if (mScreenType == OPTIONS)
		{
			mOptionsSwitchList.at(BUTTON_PLAY_DIFFICULTY)->advanceCurrentTextString();
			EventSystem::getInstance()->fireEvent(ChangeDifficultyEvent());
		}

		break;

	case BUTTON_LOAD_SOUND:
		if (mScreenType == TITLE)
		{
			EventSystem::getInstance()->fireEvent(LoadGameEvent());
		}
		
		else if (mScreenType == OPTIONS)
		{
			mOptionsSwitchList.at(BUTTON_LOAD_SOUND)->advanceCurrentTextString();
			EventSystem::getInstance()->fireEvent(ToggleAudioEvent());
		}

		break;

	case BUTTON_OPTIONS_LANGUAGE:
		if (mScreenType == TITLE)
		{
			setScreenType(OPTIONS);
			mpCursor->setSelectedButton(BUTTON_PLAY_DIFFICULTY);
		}

		else if (mScreenType == OPTIONS)
		{
			mpLanguage->nextLanguage();
		}
		break;

	case BUTTON_QUIT_RETURN:
		if (mScreenType == TITLE)
		{
			EventSystem::getInstance()->fireEvent(ExitGameEvent());
		}

		else if (mScreenType == OPTIONS)
		{
			setScreenType(TITLE);
			mpCursor->setSelectedButton(BUTTON_PLAY_DIFFICULTY);
		}

		break;
	}
}

// counts down the duration of the between levels screens
void ScreenManager::countdownToLevel()
{
	if (mCountdownTimer >= mCountdownMax)
	{
		mCountdownTimer = 0;
		EventSystem::getInstance()->fireEvent(StartLevelGameplayEvent());
	}

	mCountdownTimer++;
}

// counts down the duration of the game over screen
void ScreenManager::countdownFromGameOver()
{
	if (mCountdownTimer >= mCountdownGameOverMax)
	{
		mCountdownTimer = 0;
		setScreenType(TITLE);
	}

	mCountdownTimer++;
}

// counts down the duration of the win state screen
void ScreenManager::countdownFromWinState()
{
	if (mCountdownTimer >= mCountdownWinStateMax)
	{
		mCountdownTimer = 0;
		setScreenType(TITLE);
	}

	mCountdownTimer++;
}