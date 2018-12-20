#pragma once

#include <Trackable.h>
#include "Vector2D.h"
#include "Grid.h"

#include <vector>
#include <string>

class GridManager : public Trackable
{
public:
	GridManager(std::string filename);
	~GridManager();

	void init(int displayWidth, int displayHeight);

	// accessors
	int getGridScale();
	float getImageScale();
	int getWidth();
	int getHeight();
	int getGridArea();

	// checks or changes a space's availability
	bool checkAvailability(Vector2D gridPos);
	void changeAvailability(Vector2D gridPos, bool availability);
	bool checkPowerup(Vector2D gridPos);
	void changePowerup(Vector2D gridPos, bool containsPowerup);

private:
	std::vector<Grid> mGrid;

	std::string mDataFile;

	// information used to determine grid size
	int mX;
	int mY;

	int mGridScaler;
	float mImageScaler;

	bool mIsInit;
	bool mIsCleanup;
};