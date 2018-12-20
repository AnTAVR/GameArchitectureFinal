#pragma once

#include <Trackable.h>

#include "Vector2D.h"

class Grid : public Trackable
{
public:
	Grid(Vector2D gridPos, bool isAvailable, bool powerUp);
	~Grid();

	// mutators
	void setIsAvailable(bool availability);
	void setPowerup(bool containsPowerup);

	// accessors
	Vector2D getGridPos();
	bool getIsAvailable();
	bool getPowerup();

private:
	Vector2D mGridPos;
	bool mIsAvailable;
	bool mPowerup;
};