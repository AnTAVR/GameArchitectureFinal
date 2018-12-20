#pragma once

#include <Trackable.h>

#include <vector>
#include <string>
#include "Animation.h"

enum MarioAnims
{
	MARIO_IDLE = 0,
	MARIO_WALK,
	MARIO_JUMP
};

class GameObjectAnimator : public Trackable
{
public:
	GameObjectAnimator(std::string filename);
	~GameObjectAnimator();

	void init(int objectType);
	void cleanup();

	void update();

	void addAnimation(Animation* newAnim);
	void setAnimation(int animNumber);
	void setAnimationFrame(int animFrame) { mCurrentFrame = animFrame; }

	int getCurrentAnimation();
	int getCurrentFrame();
	int getNumAnimStates() { return mNumAnimStates; }
	Animation* getAnimation();

private:
	int mCurrentAnimation;
	int mCurrentFrame;
	int mFrameCounter;

	int mAnimationSpeed;
	int mNumAnimStates;

	std::string mDataFile;
	std::vector<Animation*> mAnimationList;
	std::vector<GraphicsBuffer*> mTempList;

	bool mIsInit;
	bool mIsCleanup;
};