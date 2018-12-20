#pragma once
#include "Event.h"

// the AddCoinsEvent class
class AddCoinsEvent : public Event
{
public:
	AddCoinsEvent(int score);
	~AddCoinsEvent();

	int getCoins() const;

private:
	int mCoins;
};