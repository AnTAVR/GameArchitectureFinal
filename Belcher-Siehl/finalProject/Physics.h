#pragma once

#include <iostream>
#include <Vector2D.h>
#include <cmath>
//#include "GameObject.h"

// physics is the holder of the Game Object's movements
class Physics
{
public:
	// constructors and deconstructors
	Physics();

	~Physics();

	// "hitbox bounds"
	void setPos(Vector2D objPos) { mGameObjectPos = objPos; }
	void setHitBoxes(float width, float height) { mHitBoxWidth = width; mHitBoxHeight = height; }

	void init(int objectType, std::string filename);

	//bool checkCollision(GameObject* other);

	// mutators
	void setMinWalkSpeed(float newSpeed) { mMinWalkSpeed = newSpeed; }
	void setCurrentSpeed(float newSpeed);
	void setMaxWalkSpeed(float newSpeed) { mMaxWalkSpeed = newSpeed; }
	void setMinRunSpeed() { mMinRunSpeed = mMaxWalkSpeed; }
	void setMaxRunSpeed(float newSpeed) { mMaxRunSpeed = newSpeed; }
	void setAcceleration(float newAccel) { mAcceleration = newAccel; }
	void setGravitySpeed(float newGravity) { mMinWalkSpeed = newGravity; }


	// accessors
	float getMinSpeed() { return mMinWalkSpeed; }
	float getCurrentSpeed() { return mCurrentSpeed; }
	float getMaxSpeed() { return mMaxWalkSpeed; }
	float getAcceleration() {return mAcceleration; }
	float getGravitySpeed() { return mGravity;}
	Vector2D getCollisionBoxes() { return Vector2D(mHitBoxWidth, mHitBoxHeight); }

private:
	Vector2D mGameObjectPos;
	float mHitBoxWidth;
	float mHitBoxHeight;

	float mMinWalkSpeed;	
	float mMaxWalkSpeed;
	float mCurrentSpeed;
	float mMinRunSpeed;
	float mMaxRunSpeed;
	float mAcceleration;
	float mGravity;

	bool mIsInit;
};