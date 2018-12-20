#include "HUD.h"
#include "Color.h"
#include "GraphicsBuffer.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// constructor for the HUD class
HUD::HUD(string filename)
{
	mDataFile = filename;

	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the HUD class
HUD::~HUD()
{
	cleanup();
}

// initializes all values for the HUD class
void HUD::init(Language* mpLanguage)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		string temp;

		int numHUDButtons, numTopScoreButtons, numBetweenLevelsButtons, numGameOverButtons, numWinStateButtons;

		const string NUM_HUD_PLACEMENTS = "NUM HUD PLACEMENTS";
		const string NUM_HUD_BUTTONS = "NUM HUD BUTTONS";
		const string NUM_TOP_SCORE_BUTTONS = "NUM TOP SCORE BUTTONS";
		const string NUM_BETWEEN_LEVELS_BUTTONS = "NUM BETWEEN LEVELS BUTTONS";
		const string NUM_GAME_OVER_BUTTONS = "NUM GAME OVER BUTTONS";
		const string NUM_WIN_STATE_BUTTONS = "NUM WIN STATE BUTTONS";

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

			pos = line.find(NUM_HUD_PLACEMENTS);
			if (pos != string::npos)
			{
				fin >> mScorePlacements >> mCoinPlacements >> mTimePlacements;
			}

			pos = line.find(NUM_HUD_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numHUDButtons;
			}

			pos = line.find(NUM_TOP_SCORE_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numTopScoreButtons;
			}

			pos = line.find(NUM_BETWEEN_LEVELS_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numBetweenLevelsButtons;
			}

			pos = line.find(NUM_GAME_OVER_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numGameOverButtons;
			}

			pos = line.find(NUM_WIN_STATE_BUTTONS);
			if (pos != string::npos)
			{
				fin >> numWinStateButtons;
			}
		}

		fin.clear();
		fin.close();


		// creates the buttons that display the HUD
		for (int i = 0; i < numHUDButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mHUDButtonList.push_back(pTempButton);
			mHUDButtonList.at(i)->init(mDataFile, HEADS_UP_DISPLAY, mpLanguage->getNumLanguages());
		}

		// creates the buttons that display the high score on the title screen
		for (int i = 0; i < numTopScoreButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mTopScoreButtonList.push_back(pTempButton);
			mTopScoreButtonList.at(i)->init(mDataFile, TOP_SCORE_DISPLAY, mpLanguage->getNumLanguages());
		}

		// creates the buttons that display the high score on the title screen
		for (int i = 0; i < numBetweenLevelsButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mBetweenLevelsButtonList.push_back(pTempButton);
			mBetweenLevelsButtonList.at(i)->init(mDataFile, BETWEEN_LEVELS_DISPLAY, mpLanguage->getNumLanguages());
		}

		// creates the buttons that display the game over text
		for (int i = 0; i < numGameOverButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mGameOverButtonsList.push_back(pTempButton);
			mGameOverButtonsList.at(i)->init(mDataFile, GAME_OVER_DISPLAY, mpLanguage->getNumLanguages());
		}

		// creates the buttons that display the win state text
		for (int i = 0; i < numWinStateButtons; i++)
		{
			Button* pTempButton = new Button(i);
			mWinStateButtonsList.push_back(pTempButton);
			mWinStateButtonsList.at(i)->init(mDataFile, WIN_STATE_DISPLAY, mpLanguage->getNumLanguages());
		}

		mIsInit = true;
	}
}

// cleans up all values for the HUD class
void HUD::cleanup()
{
	if (!mIsCleanup)
	{
		delete mpFont;

		for (unsigned i = 0; i < mHUDButtonList.size(); i++)
		{
			delete mHUDButtonList.at(i);
		}
		mHUDButtonList.clear();

		for (unsigned i = 0; i < mTopScoreButtonList.size(); i++)
		{
			delete mTopScoreButtonList.at(i);
		}
		mTopScoreButtonList.clear();

		for (unsigned i = 0; i < mBetweenLevelsButtonList.size(); i++)
		{
			delete mBetweenLevelsButtonList.at(i);
		}
		mBetweenLevelsButtonList.clear();

		for (unsigned i = 0; i < mGameOverButtonsList.size(); i++)
		{
			delete mGameOverButtonsList.at(i);
		}
		mGameOverButtonsList.clear();

		for (unsigned i = 0; i < mWinStateButtonsList.size(); i++)
		{
			delete mWinStateButtonsList.at(i);
		}
		mWinStateButtonsList.clear();

		mIsCleanup = true;
	}
}

// draws all values for the HUD
void HUD::drawHUD(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData)
{
	// draws the acting character's name and current score
	mHUDButtonList.at(SCORE_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
	mHUDButtonList.at(SCORE_VALUE)->drawButton(pSystem, setDisplay(mScorePlacements, pPermanentGameData->getScore()));

	// sets the display for and draws the current number of coins
	mHUDButtonList.at(COINS_VALUE)->drawButton(pSystem, "*" + setDisplay(mCoinPlacements, pPermanentGameData->getCoins()));

	// sets the display for and draws the current world's name
	mHUDButtonList.at(WORLD_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
	mHUDButtonList.at(WORLD_VALUE)->drawButton(pSystem, " " + to_string(pLevelManager->getCurrentLevel()->getWorld()) + "-" + to_string(pLevelManager->getCurrentLevel()->getLevel()));

	// sets the display for and draws the current timer
	mHUDButtonList.at(TIME_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
	if (pLevelManager->getOnLevel())
	{
		mHUDButtonList.at(TIME_VALUE)->drawButton(pSystem, " " + setDisplay(mTimePlacements, pLevelManager->getCurrentLevel()->getTimer()));
	}
}

// draws the player's current score
void HUD::drawHighScore(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData)
{
	mTopScoreButtonList.at(TOP_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
	mTopScoreButtonList.at(TOP_VALUE)->drawButton(pSystem, setDisplay(mScorePlacements, pPermanentGameData->getHighScore()));
}

// draws the player's current level and lives
void HUD::drawBetweenLevels(System* pSystem, LevelManager* pLevelManager, Language* pLanguage, PermanentGameData* pPermanentGameData)
{
	mBetweenLevelsButtonList.at(WORLD_TEXT_CENTER)->drawButton(pSystem, pLanguage->getLanguage());
	mBetweenLevelsButtonList.at(WORLD_VALUE_CENTER)->drawButton(pSystem, to_string(pLevelManager->getCurrentLevel()->getWorld()) + "-" + to_string(pLevelManager->getCurrentLevel()->getLevel()));

	mBetweenLevelsButtonList.at(LIVES_VALUE)->drawButton(pSystem, to_string(pPermanentGameData->getLives()));
}

// draws the game over text
void HUD::drawGameOver(System* pSystem, Language* pLanguage)
{
	mGameOverButtonsList.at(GAME_OVER_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
}

// draws the win state text
void HUD::drawWinState(System* pSystem, Language* pLanguage)
{
	mWinStateButtonsList.at(WIN_STATE_TEXT)->drawButton(pSystem, pLanguage->getLanguage());
}

// sets the amount of zeros in the display
string HUD::setDisplay(int numPlaces, int passedValue)
{
	string displayValue;

	const int DIVIDER = 10;
	int number = passedValue;
	int digits = 0;

	if (number <= 0)
	{
		digits = 1;
	}

	while (number > 0)
	{
		number /= DIVIDER;
		digits++;
	}

	for (int i = 0; i < (numPlaces - digits); i++)
	{
		displayValue += "0";
	}

	displayValue += to_string(passedValue);
	return displayValue;
}

// calculates the frame rate to the second decimal
void HUD::calculateFrameRate(float frameRate)
{
	frameRate = mFrameDivider / frameRate;

	// rounds the frame either up or down to the nearest integer
	mFrameRate = (int)nearbyint(frameRate);
}

// increases the player's score
void HUD::addPoints(int points, int scoreMultiplier)
{
	mScore = mScore + (points * scoreMultiplier);
}