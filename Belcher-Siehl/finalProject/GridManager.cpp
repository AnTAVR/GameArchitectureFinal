#include "GridManager.h"

#include <fstream>

using namespace std;

// constructor for the GridManager class
GridManager::GridManager(string filename)
{
	mDataFile = filename;

	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the GridManager class
GridManager::~GridManager()
{
	
}

// initializes the grid for a given level
void GridManager::init(int displayWidth, int displayHeight)
{
	if (!mIsInit)
	{
		ifstream fin;
		int gridFiller = 0;
		size_t pos;
		string line;

		const string GRID_SCALER = "GRID SCALER";
		const string IMAGE_SCALER = "IMAGE SCALER";

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

			pos = line.find(GRID_SCALER);
			if (pos != string::npos)
			{
				fin >> mGridScaler;
			}

			pos = line.find(IMAGE_SCALER);
			if (pos != string::npos)
			{
				fin >> mImageScaler;
			}
		}

		fin.clear();
		fin.close();

		mX = displayWidth / mGridScaler;
		mY = displayHeight / mGridScaler;

		// populates the grid with "true" availability and "false" powerup values
		for (int i = 0; i < mX; i++)
		{
			for (int j = 0; j < mY; j++)
			{
				mGrid.push_back(Grid(Vector2D(i, j), true, false));
				gridFiller++;
			}
		}
	}
}

// returns the availability of a certain space
bool GridManager::checkAvailability(Vector2D gridLoc)
{
	for (unsigned i = 0; i < mGrid.size(); i++)
	{
		if (mGrid.at(i).getGridPos() == gridLoc)
		{
			if (mGrid.at(i).getIsAvailable())
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}

	// if the space does not exist on the grid, exit the stage
	return false;
}

// changes whether or not a space is available
void GridManager::changeAvailability(Vector2D gridLoc, bool availability)
{
	for (unsigned i = 0; i < mGrid.size(); i++)
	{
		if (mGrid.at(i).getGridPos() == gridLoc)
		{
			mGrid.at(i).setIsAvailable(availability);
			break;
		}
	}
}

// returns whether or not a space contains a powerup
bool GridManager::checkPowerup(Vector2D gridLoc)
{
	for (unsigned i = 0; i < mGrid.size(); i++)
	{
		if (mGrid.at(i).getGridPos() == gridLoc)
		{
			if (mGrid.at(i).getPowerup())
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}

	// if the space does not exist, end the function gracefully
	return false;
}

// changes whether or not a space is available
void GridManager::changePowerup(Vector2D gridLoc, bool availability)
{
	for (unsigned i = 0; i < mGrid.size(); i++)
	{
		if (mGrid.at(i).getGridPos() == gridLoc)
		{
			mGrid.at(i).setPowerup(availability);
			break;
		}
	}
}

// returns the grid's scaling data
int GridManager::getGridScale()
{
	return mGridScaler;
}

// returns the image scaling data
float GridManager::getImageScale()
{
	return mImageScaler;
}

// returns the Grid's width
int GridManager::getWidth()
{
	return mX;
}

// returns the Grid's height
int GridManager::getHeight()
{
	return mY;
}

// returns the Grid's area
int GridManager::getGridArea()
{
	return (mX * mY);
}