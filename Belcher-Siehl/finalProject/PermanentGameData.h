#pragma once

#include "EventSystem.h"
#include "PlaySoundEffectEvent.h"

#include <Trackable.h>

enum PowerUps
{
	SMALL = 0
};

enum Values
{
	MAX_SCORE = 999999,
	MAX_COINS = 100,
	STARTING_LIVES = 3
};

enum DifficultyLevels
{
	EASY = 0,
	NORMAL,
	HARD
};

class PermanentGameData : public Trackable
{
public:
	PermanentGameData();
	~PermanentGameData();

	void addScore(int newPoints);
	void addCoins(int newCoins);
	void addLives(int newLives);
	void changePowerUpState(int newPowerUp);
	void nextDifficulty();

	void setScore(int score) { mScore = score; }
	void setHighScore(int highScore) { mHighScore = highScore; }
	void setCoins(int coins) { mCoins = coins; }
	void setLives(int lives) { mLives = lives; }
	void setPowerUp(int powerUp) { mPowerUp = powerUp; }
	void setDifficulty(int difficulty) { mDifficulty = difficulty; }

	int getScore() { return mScore; }
	int getHighScore() { return mHighScore; }
	int getCoins() { return mCoins; }
	int getLives() { return mLives; }
	int getPowerUp() { return mPowerUp; }
	int getDifficulty() { return mDifficulty; }

private:
	int mHighScore;
	int mScore;
	int mCoins;
	int mLives;
	int mPowerUp;
	int mDifficulty;
};