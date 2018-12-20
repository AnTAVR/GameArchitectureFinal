#include "Physics.h"
#include "GameObject.h"

#include <fstream>

using namespace std;

Physics::Physics()
{
	mMinWalkSpeed = 0.0f;
	mMaxWalkSpeed = 0.0f;
	mCurrentSpeed = 0.0f;
	mMinRunSpeed = 0.0f;
	mMaxRunSpeed = 0.0f;
	mAcceleration = 0.0f;
	mGravity = 0.0f;

	mIsInit = false;
}

Physics::~Physics()
{

}

void Physics::init(int objectType, string filename)
{
	if (!mIsInit)
	{
		// variables used for reading in from the file
		ifstream fin;
		size_t pos;
		string line;

		int tempX, tempY;
			
		const string PHYSICS_PARAMS = "PHYSICS PARAMS";
		const string HITBOX_SIZE = "HITBOX_SIZE";

		fin.open(filename);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// pulls in the game's universal physics parameters
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(PHYSICS_PARAMS);
			if (pos != string::npos)
			{
				fin >> mMinWalkSpeed >> mMaxWalkSpeed >> mMaxRunSpeed >> mAcceleration >> mGravity;
				mMinRunSpeed = mMaxWalkSpeed;
			}

			pos = line.find(HITBOX_SIZE);
			if (pos != string::npos)
			{
				fin >> tempX >> tempY;
				setHitBoxes((float)tempX, (float)tempY);
			}
		}

		fin.clear();
		fin.close();

		mIsInit = true;
	}
}

void Physics::setCurrentSpeed(float newSpeed)
{
	if (newSpeed < mMaxWalkSpeed && newSpeed > mMinWalkSpeed)
	{
		mCurrentSpeed = newSpeed;
	}
	else if (newSpeed > mMaxRunSpeed)
	{
		mCurrentSpeed = mMaxRunSpeed;
	}
	else if (newSpeed < mMinWalkSpeed)
	{
		mCurrentSpeed = mMinWalkSpeed;
	}
	else
	{
		mCurrentSpeed = mCurrentSpeed;
	}
}
