#include "PermanentGameData.h"
#include "KillPlayerCharacterEvent.h"

// constructor for the PermanentGameData class
PermanentGameData::PermanentGameData()
{
	mScore = 0;
	mHighScore = 0;
	mCoins = 0;
	mLives = STARTING_LIVES;
	mPowerUp = SMALL;
	mDifficulty = 0;
}

// destructor for the PermanentGameData class
PermanentGameData::~PermanentGameData()
{
	
}

// adds a preset value to the player's current score
void PermanentGameData::addScore(int newPoints)
{
	mScore += newPoints;

	if (mScore >= MAX_SCORE)
	{
		mScore = MAX_SCORE;
	}
	
	if (mScore > mHighScore)
	{
		mHighScore = mScore;
	}
}

// adds a preset value to the player's current coins
void PermanentGameData::addCoins(int newCoins)
{
	EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(EARN_COIN));
	mCoins += newCoins;

	if (mCoins >= MAX_COINS)
	{
		mCoins -= MAX_COINS;
		addLives(1);
	}
}

// adds a preset value to the player's current lives
void PermanentGameData::addLives(int newLives)
{
	if (newLives > 0)
	{
		EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(ONE_UP));
	}

	mLives += newLives;
}

// changes the player's current PowerUp state in some way
void PermanentGameData::changePowerUpState(int newPowerUp)
{
	// grants the player a powerup
	if (mPowerUp + newPowerUp >= 0)
	{
		
	}

	// kills the player
	else
	{
		EventSystem::getInstance()->fireEvent(KillPlayerCharacterEvent());
	}
}

// changes the current difficulty level
void PermanentGameData::nextDifficulty()
{
	if (mDifficulty >= HARD)
	{
		mDifficulty = EASY;
	}

	else
	{
		mDifficulty++;
	}
}