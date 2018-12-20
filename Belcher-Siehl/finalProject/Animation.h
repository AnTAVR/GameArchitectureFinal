#pragma once

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <vector>

class Sprite;
class GraphicsBuffer;

class Animation : public Trackable
{
public:
	// constructor and destructor
	Animation(int numSprites, int initialSpeed);
	~Animation();

	// add sprites
	void addSprites(Sprite* sprite);
	void loadSpriteSheet(GraphicsBuffer* animationSheet, int sheetWidth, int sheetHeight, int spriteWidth, int spriteHeight);

	// update to discover the "current" sprite
	void update(int frame);

	// accessors
	Sprite* getCurrentSprite();
	int getNumSprites();

	// change animation speed
	int speedUp();
	int slowDown();

private:
	std::vector <Sprite*> mpSpriteList;		// list of Sprites used in the animation
	int mTimingInfo;						// determines speed of the animation
	int mCurrentSprite;						// the current Sprite being viewed

	int mNumSprites;						// the total number of Sprites in the animation

											// determine if the animation should loop or if the object is destroyed
	bool mShouldLoop;
};