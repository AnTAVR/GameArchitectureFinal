#include "GameObject.h"
#include "Sprite.h"
#include "EventSystem.h"
#include "PlaySoundEffectEvent.h"
#include "SetPowerUpEvent.h"
#include "ScorePointsEvent.h"
#include "AddCoinsEvent.h"
#include "KillPlayerCharacterEvent.h"
#include "Game.h"

#include <fstream>

using namespace std;

// constructor for the GameObject class
GameObject::GameObject(int objectType, Vector2D loc, bool exists)
{
	mCanMove = true;

	mLoc = loc;
	mExists = exists;
	mIsInit = false;
	mIsCleanup = false;

	mIsDestroyed = false;

	mRightFacing = true;
	mRightMoving = false;
	mGrounded = true;
	mJumping = false;
	mType = objectType;
}

// destructor for the GameObject class
GameObject::~GameObject()
{
	cleanup();
}

// initializes all values in the GameObject class
void GameObject::init(string filename)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		const string JUMP_SPEED = "JUMP SPEED";
		const string MAX_INVINCIBILITY_FRAMES = "MAX INVINCIBILITY FRAMES";

		const string GOOMBA_POINTS = "GOOMBA POINTS";
		const string COIN_POINTS = "COIN POINTS";
		const string BRICK_POINTS = "BRICK POINTS";

		fin.open(filename);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(JUMP_SPEED);
			if (pos != string::npos)
			{
				fin >> mJumpSpeed;
			}

			pos = line.find(GOOMBA_POINTS);
			if (pos != string::npos && mType == GOOMBA)
			{
				fin >> mPointValue;
			}

			pos = line.find(COIN_POINTS);
			if (pos != string::npos && mType == COIN)
			{
				fin >> mPointValue;
			}

			pos = line.find(BRICK_POINTS);
			if (pos != string::npos && mType == BRICK)
			{
				fin >> mPointValue;
			}
		}

		fin.clear();
		fin.close();

		mpGameObjectAnimator = new GameObjectAnimator(filename);
		mPhysics = Physics();
		mPhysics.init(mType, filename);

		mpGameObjectAnimator->init(mType);

		mStartingX = (int)mLoc.getX();
		mStartingY = (int)mLoc.getY();

		mIsInit = true;
	}
}

// cleans up all values in the GameObject class
void GameObject::cleanup()
{
	if (!mIsCleanup)
	{
		delete mpGameObjectAnimator;

		mIsCleanup = true;
	}
}

// updates all facets of the GameObject
void GameObject::update()
{
	mpGameObjectAnimator->update();
	// update position based on physics
	updateJump();
	
	if(!mJumping && !mGrounded)
	{
		fall();
	}

	if (mLoc.getY() > KILL_PLAIN)
	{
		if (mType == MARIO)
		{
			EventSystem::getInstance()->fireEvent(KillPlayerCharacterEvent());
		}

		else
		{
			this->setIsDestroyed(true);
		}
	}
}

void GameObject::move(std::string direction)
{
	if (mCanMove)
	{
		if (direction == "right")
		{
			mRightMoving = true;
			if (mLoc.getX() < 447 || mType == GOOMBA)
			{
				mOverTheLine = false;
				float newPosX = mLoc.getX() + mPhysics.getCurrentSpeed();
				mLoc.setX(newPosX);
				mPhysics.setCurrentSpeed(mPhysics.getCurrentSpeed() + mPhysics.getAcceleration());
				mRightFacing = true;
			}
			else {
				mOverTheLine = true;
			}

		}

		if (direction == "left")
		{
			mLeftMoving = true;

				if (mLoc.getX() > 0 || mType == GOOMBA)
				{
					float newPosX = mLoc.getX() - mPhysics.getCurrentSpeed();
					mLoc.setX(newPosX);
					mPhysics.setCurrentSpeed(mPhysics.getCurrentSpeed() + mPhysics.getAcceleration());
					mRightFacing = false;
				}
				else {
					//return;
				}

		}
	}
}

void GameObject::moveScreen()
{
	float newPosX = mLoc.getX() - mPhysics.getCurrentSpeed();
	mLoc.setX(newPosX);

	mPhysics.setCurrentSpeed(mPhysics.getCurrentSpeed() + mPhysics.getAcceleration());
}

bool GameObject::onRightScreen()
{
	return mOverTheLine;
}

void GameObject::notMoving()
{
	if (!mJumping)
	{
		mLeftMoving = false;
		mRightMoving = false;
	}
}

void GameObject::initJump()
{
	// check for grounded
	// if so then save the maxY and set jump bool to true
	// save maxY for jump
	if (mGrounded && !mJumping) 
	{
		if (Game::getInstance()->getPermanentGameData()->getPowerUp() == SMALL)
		{
			EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(JUMP_SMALL));
		}

		mMaxY = mLoc.getY() - (mJumpSpeed * 40); // down is larger than up
		mJumping = true;

	}

}

void GameObject::updateJump()
{
	if (mJumping)
	{
		mGrounded = false;
		if (mLoc.getY() > mMaxY)
		{
			mpGameObjectAnimator->setAnimation(MARIO_JUMP * getAnimator()->getNumAnimStates() + Game::getInstance()->getPermanentGameData()->getPowerUp());
			float newPosY = mLoc.getY() - mJumpSpeed;

			mLoc.setY(newPosY);
		}
		else {
			
			mJumping = false;
		}
	}
	else 
	{
		return;
	}

}

void GameObject::fall()
{
	mpGameObjectAnimator->setAnimation(MARIO_JUMP * getAnimator()->getNumAnimStates() + Game::getInstance()->getPermanentGameData()->getPowerUp());

	float newPosY = mLoc.getY() + mJumpSpeed;

	mLoc.setY(newPosY);

}

void GameObject::setCanMoveBool(GameObject* obj)
{
	float playRight = mLoc.getX() + MARIO_COLLISION_ADJUSTER_7; // the right side of mario
	float playLeft = mLoc.getX();

	float objLeft = obj->getLoc().getX();
	float objRight = obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_7; // right side of the object

	bool rightCollided = false;
	bool leftCollided = false;


	// check for collision for moving left and right
	if (objLeft <= playRight && objRight >= playRight)
		rightCollided = true;
	if (playLeft <= objRight && playRight >= objRight)
		leftCollided = true;


	// right and left collision for moving and not moving
	if (mRightMoving && !obj->getDestroyed())
	{
		if (rightCollided && ((mLoc.getY() + MARIO_COLLISION_ADJUSTER_7 >= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_7 < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_7) ||
			(mLoc.getY() + MARIO_COLLISION_ADJUSTER_7 <= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_5 > obj->getLoc().getY())))
		{
			if (obj->getType() == GOOMBA)
			{
				// injure mario
				if (mType == MARIO)
				{
					mRightMoving = false;
					EventSystem::getInstance()->fireEvent(PowerUpEvent(-1));
				}
			}

			else if (obj->getType() == COIN)
			{
				obj->setIsDestroyed(true);
				EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
				EventSystem::getInstance()->fireEvent(AddCoinsEvent(1));
			}

			else if (obj->getType() == FLAG_POLE)
			{
				EventSystem::getInstance()->fireEvent(END_OF_LEVEL_EVENT);
			}
			else if (obj->getType() == FLAG)
			{
				EventSystem::getInstance()->fireEvent(END_OF_LEVEL_EVENT);
			}
			else 
			{
				mRightMoving = false;
			}

		}
		else
		{
			mRightMoving = true;
		}

	}
	else if (mLeftMoving && !obj->getDestroyed())
	{
		if (leftCollided && ((mLoc.getY() >= obj->getLoc().getY() && mLoc.getY() < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_7) ||
			(mLoc.getY() <= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_5 > obj->getLoc().getY())))
		{
			if (obj->getType() == GOOMBA)
			{
				// injure mario
				if (mType == MARIO)
				{
					mLeftMoving = false;
					EventSystem::getInstance()->fireEvent(PowerUpEvent(-1));
				}


			}

			else if (obj->getType() == COIN)
			{
				obj->setIsDestroyed(true);
				EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
				EventSystem::getInstance()->fireEvent(AddCoinsEvent(1));
			}
			else if (obj->getType() == FLAG_POLE)
			{
				EventSystem::getInstance()->fireEvent(END_OF_LEVEL_EVENT);
				mFlagContact = true;

			}
			else if (obj->getType() == FLAG)
			{
				EventSystem::getInstance()->fireEvent(END_OF_LEVEL_EVENT);
				mFlagContact = true;
			}
			else
			{
				mLeftMoving = false;
			}
		}
		else
		{
			mLeftMoving = true;
		}
	}
	else
	{
		if (rightCollided && ((mLoc.getY() >= obj->getLoc().getY() && mLoc.getY() < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_7) ||
			(mLoc.getY() <= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_4 > obj->getLoc().getY())))
		{
			if (obj->getType() == GOOMBA)
			{
				// injure mario
				if (mType == MARIO)
				{
					mRightMoving = false;
					EventSystem::getInstance()->fireEvent(PowerUpEvent(-1));
				}
			}

			else if (obj->getType() == COIN)
			{
				obj->setIsDestroyed(true);
				EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
				EventSystem::getInstance()->fireEvent(AddCoinsEvent(1));
			}


			else if (obj->getType() == FLAG_POLE)
			{
				EventSystem::getInstance()->fireEvent(END_OF_LEVEL_EVENT);
				mFlagContact = true; // to prevent the spamming of the sound
			}

		}
	}

	// fall collision
	if ((obj->getLoc().getX() <= mLoc.getX() + MARIO_COLLISION_ADJUSTER_1 && obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_7 >= mLoc.getX() + MARIO_COLLISION_ADJUSTER_1 ||
		(mLoc.getX() <= obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_2 && mLoc.getX() + MARIO_COLLISION_ADJUSTER_7 >= obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_2)) &&
		mLoc.getY() < obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_1 + MARIO_COLLISION_ADJUSTER_3 > obj->getLoc().getY() && !obj->getDestroyed())
	{
		if (obj->getType() == GOOMBA)
		{
			//kill goomba
			EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(STOMP));
			EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
			obj->setIsDestroyed(true);

			// jump
			mJumping = true;
			mMaxY = mLoc.getY() - MARIO_COLLISION_ADJUSTER_7;

		}

		else if (obj->getType() == COIN)
		{
			obj->setIsDestroyed(true);
			EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
			EventSystem::getInstance()->fireEvent(AddCoinsEvent(1));
		}

		else
		{
			mGrounded = true;
		}
	}
	else
		mGrounded = false;

	// jump collision
	if (mLoc.getY() > obj->getLoc().getY() && mLoc.getY() < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_6 &&
		(mLoc.getX() + MARIO_COLLISION_ADJUSTER_1 >= obj->getLoc().getX() && mLoc.getX() <= obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_1)
		&& obj->getType() != COIN)
	{
		if (obj->getType() == BRICK)
		{
			EventSystem::getInstance()->fireEvent(PlaySoundEffectEvent(BREAK_BLOCK));
			EventSystem::getInstance()->fireEvent(ScorePointsEvent(obj->getPointValue()));
			obj->setIsDestroyed(true);
		}
		else if (obj->getType() == GOOMBA)
		{
			EventSystem::getInstance()->fireEvent(PowerUpEvent(-1));
		}
		mJumping = false;

	}

}

void GameObject::hardCodeGoomba(GameObject* obj)
{
	float playRight = mLoc.getX() + MARIO_COLLISION_ADJUSTER_7;
	float playLeft = mLoc.getX();

	float objLeft = obj->getLoc().getX();
	float objRight = obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_7;

	bool rightCollided = false;
	bool leftCollided = false;


	// check for collision for moving left and right
	if (objLeft <= playRight && objRight >= playRight)
		rightCollided = true;
	if (playLeft <= objRight && playRight >= objRight)
		leftCollided = true;

	if (mRightMoving && !obj->getDestroyed())
	{
		if (obj->getType() != MARIO)
		{
			if (rightCollided && ((mLoc.getY() >= obj->getLoc().getY() && mLoc.getY() < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_7) ||
				(mLoc.getY() <= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_7 > obj->getLoc().getY())))
			{
				mRightMoving = false;
				mLeftMoving = true;
			}
		}
		else
		{
			mRightMoving = true;

		}

	}

	if (mLeftMoving && !obj->getDestroyed())
	{
		if (obj->getType() != MARIO)
		{
			if (leftCollided && ((mLoc.getY() >= obj->getLoc().getY() && mLoc.getY() < obj->getLoc().getY() + MARIO_COLLISION_ADJUSTER_7) ||
				(mLoc.getY() <= obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_7 > obj->getLoc().getY())))
			{
				mLeftMoving = false;
				mRightMoving = true;
			}
		}
		else
		{
			mLeftMoving = true;

		}
	}

	mPhysics.setCurrentSpeed(mPhysics.getMaxSpeed() / 2);

	if ((obj->getLoc().getX() <= mLoc.getX() + MARIO_COLLISION_ADJUSTER_1 && obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_7 >= mLoc.getX() + MARIO_COLLISION_ADJUSTER_1 ||
		(mLoc.getX() <= obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_2 && mLoc.getX() + MARIO_COLLISION_ADJUSTER_7 >= obj->getLoc().getX() + MARIO_COLLISION_ADJUSTER_2)) &&
		mLoc.getY() < obj->getLoc().getY() && mLoc.getY() + MARIO_COLLISION_ADJUSTER_3 > obj->getLoc().getY() && !obj->getDestroyed())
	{
		if (obj->getType() != MARIO)
			mGrounded = true;
	}
	else
		mGrounded = false;
}

// draws the GameObject at its current location
void GameObject::draw(GraphicsSystem* pSystem)
{
	pSystem->draw(mLoc.getX(), mLoc.getY(), mpGameObjectAnimator->getAnimation()->getCurrentSprite(), 1.0f, mRightFacing);
}

// sets mLocX's value
void GameObject::setLocX(float locX)
{
	mLoc.setX(locX);
}

// sets mLocY's value
void GameObject::setLocY(float locY)
{
	mLoc.setY(locY);
}

// gets the GameObject's y position
Vector2D GameObject::getLoc()
{
	return mLoc;
}

// checks whether or not the GameObject currently "exists" on the screen
bool GameObject::getExists()
{
	return mExists;
}
