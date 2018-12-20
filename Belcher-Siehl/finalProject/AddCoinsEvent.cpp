#include "AddCoinsEvent.h"

// constructor for the AddCoinsEvent class
AddCoinsEvent::AddCoinsEvent(int coins)
	: Event(ADD_COINS_EVENT)
{
	mCoins = coins;
}

// destructor for the ScorePointsEvent class
AddCoinsEvent::~AddCoinsEvent()
{

}

// returns the amount of points earned for eating food
int AddCoinsEvent::getCoins() const
{
	return mCoins;
}