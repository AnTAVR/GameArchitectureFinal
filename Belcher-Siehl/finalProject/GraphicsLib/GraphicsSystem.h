#pragma once

#include "Font.h"
#include "Color.h"
#include "Sprite.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <string>

class GraphicsBuffer;

// the GraphicsSystem class
class GraphicsSystem : public Trackable
{
public:
	// constructor
	GraphicsSystem();

	// destructor
	~GraphicsSystem();

	// initializes all aspects of the graphics system
	int init(int width, int height);

	// destroys the display
	void cleanup();

	// accessors
	int getWidth();
	int getHeight();
	GraphicsBuffer* getBuffer();

	// flips the display
	void flip();

	// draws a sprite to a target location
	void draw(float locX, float locY, Sprite* pSprite, float scale, bool isRightFacing);
	void draw(GraphicsBuffer* pTarget, float locX, float locY, Sprite* pSprite, float scale, bool isRightFacing);

	// writes text to a target location
	void writeText(float locX, float locY, Font* font, Color &color, std::string text);
	void writeText(GraphicsBuffer* pTarget, float locX, float locY, Font &font, Color &color, std::string text);

	// saves the target GraphicsBuffer
	void saveBuffer(GraphicsBuffer* pTarget, std::string filename);

	// friends
	friend class GraphicsBuffer;

private:
	SDL_Window* mpWindow;
	SDL_Renderer* mpRenderer;
	GraphicsBuffer* mpBackbuffer;

	int mWidth;
	int mHeight;

	bool mIsInit;
};