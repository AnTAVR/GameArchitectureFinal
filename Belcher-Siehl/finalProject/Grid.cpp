#include "Grid.h"

// constructor for the Grid class
Grid::Grid(Vector2D gridPos, bool isAvailable, bool powerUp)
{
	mGridPos = gridPos;
	mIsAvailable = isAvailable;
	mPowerup = powerUp;
}

// destructor for the Grid class
Grid::~Grid()
{

}

// sets the availability
void Grid::setIsAvailable(bool availability)
{
	mIsAvailable = availability;
}

// sets whether or not a space contains a powerup
void Grid::setPowerup(bool containsPowerup)
{
	mPowerup = containsPowerup;
}

// returns the grid position
Vector2D Grid::getGridPos()
{
	return mGridPos;
}

// returns the availability
bool Grid::getIsAvailable()
{
	return mIsAvailable;
}

// returns whether or not there is a powerup
bool Grid::getPowerup()
{
	return mPowerup;
}