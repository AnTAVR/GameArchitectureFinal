#pragma once
#include "Event.h"

// the ExitGameEvent class
class ScorePointsEvent : public Event
{
public:
	// constructor and destructor
	ScorePointsEvent(int score);
	~ScorePointsEvent();

	int getScore() const;

private:
	int mScore;
};