#include "ScorePointsEvent.h"

// constructor for the ScorePointsEvent class
ScorePointsEvent::ScorePointsEvent(int score)
	: Event(SCORE_POINTS_EVENT)
{
	mScore = score;
}

// destructor for the ScorePointsEvent class
ScorePointsEvent::~ScorePointsEvent()
{

}

// returns the amount of points earned for eating food
int ScorePointsEvent::getScore() const
{
	return mScore;
}