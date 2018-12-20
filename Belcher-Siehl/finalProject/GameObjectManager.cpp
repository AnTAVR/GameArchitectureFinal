#include "GameObjectManager.h"
#include "Vector2D.h"

using namespace std;

// constructor for the GameObjectManager class
GameObjectManager::GameObjectManager(string filename)
{
	mDataFile = filename;

	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the GameObjectManager class
GameObjectManager::~GameObjectManager()
{
	cleanup();
}

// initializes the GameObjectManager class
void GameObjectManager::init()
{
	if (!mIsInit)
	{
		addGameObject(MARIO, Vector2D(MARIO_START_X, MARIO_START_Y), true);

		mIsInit = true;
	}
}

// cleans up the GameObjectManager class
void GameObjectManager::cleanup()
{
	if (!mIsCleanup)
	{
		for (unsigned i = 0; i < mGameObjectList.size(); i++)
		{
			delete mGameObjectList.at(i);
		}

		mGameObjectList.clear();

		mIsCleanup = true;
	}
}

// updates every GameObject*
void GameObjectManager::update()
{
	for (unsigned i = 1; i < mGameObjectList.size(); i++)
	{
		if (mGameObjectList.at(i)->getExists() && !mGameObjectList.at(i)->getDestroyed())
		{
			if (mGameObjectList.at(i)->getLoc().getX() < UPDATE_MAX && mGameObjectList.at(i)->getLoc().getX() > UPDATE_MIN_2)
			{
				if (mGameObjectList.at(i)->getType() == GOOMBA)
				{
					// i  is the goomba and it is checkign for collisions for 
					for (unsigned j = 0; j < mGameObjectList.size(); j++)
					{
						if (j != i)
							mGameObjectList.at(i)->hardCodeGoomba(mGameObjectList.at(j));

						if (mGameObjectList.at(i)->getGroundedBool())
							break;

					}

					if (mGameObjectList.at(i)->getRightMoving())
					{
						mGameObjectList.at(i)->move("right");

					}
					else
					{
						mGameObjectList.at(i)->move("left");

					}
				}

				mGameObjectList.at(i)->update();

			}
		}
	}

	for (unsigned i = 1; i < mGameObjectList.size(); i++)
	{
		if (mGameObjectList.at(i)->getExists() && !mGameObjectList.at(i)->getDestroyed())
		{
			if (mGameObjectList.at(i)->getLoc().getX() < UPDATE_MAX && mGameObjectList.at(i)->getLoc().getX() > UPDATE_MIN)
			{

				if (mGameObjectList.at(MARIO)->getJumpBool())
				{
					mGameObjectList.at(MARIO)->setCanMoveBool(mGameObjectList.at(i));

				}
				else
				{
					if (mGameObjectList.at(i)->getLoc().getX() < mGameObjectList.at(MARIO)->getLoc().getX() + MARIO_COLLISION_ADJUSTER_4 &&
						mGameObjectList.at(i)->getLoc().getX() > mGameObjectList.at(MARIO)->getLoc().getX() - MARIO_COLLISION_ADJUSTER_4)
					{
						mGameObjectList.at(MARIO)->setCanMoveBool(mGameObjectList.at(i));

						if (mGameObjectList.at(MARIO)->getGroundedBool())
							break;
					}
				}

			}
		}
	}

	if (mGameObjectList.at(0)->getRightMoving())
	{
		mGameObjectList.at(0)->move("right");
	}

	if (mGameObjectList.at(0)->getLeftMoving())
	{
		mGameObjectList.at(0)->move("left");
	}

	mGameObjectList.at(0)->update();

}

// draws every existing GameObject*
void GameObjectManager::draw(GraphicsSystem* pSystem)
{
	for (unsigned i = 0; i < mGameObjectList.size(); i++)
	{
		if (mGameObjectList.at(i)->getExists() && !mGameObjectList.at(i)->getDestroyed())
		{
			if (mGameObjectList.at(i)->getLoc().getX() < DRAW_MAX && mGameObjectList.at(i)->getLoc().getX() >= DRAW_MIN)
				mGameObjectList.at(i)->draw(pSystem);
		}
	}
}

// adds a GameObject* to the vector
void GameObjectManager::addGameObject(int objectType, Vector2D loc, bool exists)
{
	GameObject* tempObject = new GameObject(objectType, loc, exists);
	tempObject->init(mDataFile);
	mGameObjectList.push_back(tempObject);
}

// removes a GameObject* from the vector
void GameObjectManager::removeGameObject()
{
	// removes GameObject*
}