#include "Animation.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

#include <vector>

using namespace std;

// constructor for the Animation class
Animation::Animation(int numSprites, int initialSpeed)
{
	mpSpriteList.resize(0);
	mTimingInfo = initialSpeed;
	mCurrentSprite = 0;
	mNumSprites = numSprites;

	mShouldLoop = false;
}

// destructor for the Animation class
Animation::~Animation()
{
	for (unsigned i = 0; i < mpSpriteList.size(); i++)
	{
		delete mpSpriteList.at(i);
	}

	mpSpriteList.clear();
}

// add Sprites to the Animation's mpSpriteList variable
void Animation::addSprites(Sprite* sprite)
{
	mpSpriteList.push_back(sprite);
}

// separates the given GraphicsBuffer into multiple sprites and a Animation
void Animation::loadSpriteSheet(GraphicsBuffer* animationSheet, int sheetWidth, int sheetHeight, int spriteWidth, int spriteHeight)
{
	// creates the sprites for the Smurf animation
	for (int i = 0; i < sheetWidth; i++)
	{
		for (int j = 0; j < sheetHeight; j++)
		{
			int locY = spriteHeight * i;
			int locX = spriteWidth * j;

			Sprite* pSprite = new Sprite(animationSheet, (float)locX, (float)locY, spriteWidth, spriteHeight);

			addSprites(pSprite);
		}
	}
}

// update to determine the "current" Sprite
void Animation::update(int frame)
{
	mCurrentSprite = frame;
}

// get the current Sprite in the animation
Sprite* Animation::getCurrentSprite()
{
	return mpSpriteList[mCurrentSprite];
}

// get the number of Sprites in the animation
int Animation::getNumSprites()
{
	return mNumSprites;
}

// speed up the animation
int Animation::speedUp()
{
	if (mTimingInfo > 0)
		mTimingInfo -= 1;

	return mTimingInfo;
}

// slow down the animation
int Animation::slowDown()
{
	if (mTimingInfo < 10)
		mTimingInfo += 1;

	return mTimingInfo;
}