#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <vector>
#include "Physics.h"

#include "GraphicsSystem.h"
#include "GameObjectAnimator.h"

//class EventSystem;

enum CharValues
{
	FLAG_FALL_POINTS = 50,
	FLAG_HEIGHT = 300,
	KILL_PLAIN = 1100,

	MARIO_START_X = 128,
	MARIO_START_Y = 500,

	DRAW_MIN = -75,
	DRAW_MAX = 1070,

	UPDATE_MIN = -500,
	UPDATE_MIN_2 = -70,
	UPDATE_MAX = 1100,

	MARIO_COLLISION_ADJUSTER_1 = 55,
	MARIO_COLLISION_ADJUSTER_2 = 59,
	MARIO_COLLISION_ADJUSTER_3 = 70,
	MARIO_COLLISION_ADJUSTER_4 = 100,
	MARIO_COLLISION_ADJUSTER_5 = 115,
	MARIO_COLLISION_ADJUSTER_6 = 10,
	MARIO_COLLISION_ADJUSTER_7 = 64
};

enum ObjectType
{
	MARIO = 0,

	GOOMBA,

	COIN,

	GROUND,
	SOLID_BLOCK,
	BRICK,
	QUESTION_MARK_BLOCK,

	FLAG_POLE,
	FLAG_POLE_TOP,
	FLAG,

	PIPE_BODY_LEFT,
	PIPE_BODY_RIGHT,
	PIPE_TOP_LEFT,
	PIPE_TOP_RIGHT
};

class GameObject : public Trackable
{
public:

	//constructor
	GameObject(int objectType, Vector2D loc, bool exists);

	//deconstructor
	~GameObject();

	// functions
	void init(std::string filename);
	void cleanup();
	void update();
	void move(std::string direction);
	void moveScreen();
	void updateJump();
	void fall();
	void initJump();
	void draw(GraphicsSystem* pSystem);
	void notMoving();
	void hardCodeGoomba( GameObject* obj);


	// accessors
	GameObjectAnimator* getAnimator() { return mpGameObjectAnimator; }
	bool getJumpBool() { return mJumping; }
	bool getGroundedBool() { return mGrounded; }
	bool getRightMoving() { return mRightMoving; }
	bool getLeftMoving() { return mLeftMoving; }
	bool getCanMove() { return mCanMove; }
	bool getDestroyed() { return mIsDestroyed; }
	bool getFlagContact() { return mFlagContact; }
	bool getExists();	
	bool onRightScreen();

	int getStartingX() { return mStartingX; }
	int getStartingY() { return mStartingY; }
	int getType() { return mType; }
	int getPointValue() { return mPointValue; }

	Vector2D getLoc();
	Physics getPhysics() { return mPhysics; }

	//mutators
	void setCanMoveBool(GameObject* obj);
	void setLocX(float locX);
	void setLocY(float locY);
	void setJumpBool(bool jump) { mJumping = jump; }
	void setGroundBool(bool grounded) { mGrounded = grounded; }
	void setMovingRight(bool rightMove) { mRightMoving = rightMove; }
	void setMovingLeft(bool leftMove) { mLeftMoving = leftMove; }
	void setCanMoveBoolOnLoad(bool canMove) { mCanMove = canMove; }
	void setExists(bool exists) { mExists = exists; }
	void setStartingX(int newX) { mStartingX = newX; }
	void setIsDestroyed(bool newVal) { mIsDestroyed = newVal; }

private:
	GameObjectAnimator* mpGameObjectAnimator;
	Physics mPhysics;

	Vector2D mLoc;
	int mStartingX;
	int mStartingY;

	bool mExists;

	bool mIsInit;
	bool mIsCleanup;

	bool mRightFacing;
	bool mRightMoving;
	bool mLeftMoving;
	bool mJumping;
	bool mGrounded;
	bool mIsDestroyed;

	bool mOverTheLine;
	bool mCanMove;

	float mMaxY;
	float mJumpSpeed;

	int mPointValue;

	int mType;

	bool mFlagContact;
};