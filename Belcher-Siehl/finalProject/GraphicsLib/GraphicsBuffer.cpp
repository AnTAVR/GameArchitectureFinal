#include "GraphicsBuffer.h"
#include "Color.h"
#include "GraphicsSystem.h"

using namespace std;

// constructor for the GraphicsBuffer class
GraphicsBuffer::GraphicsBuffer(string filename, bool owned) 
{
	mpSurface = IMG_Load(("Assets\\" + filename).c_str());
	mIsOwned = owned;

	mWidth = mpSurface->w;
	mHeight = mpSurface->h;
}

// constructor for the GraphicsBuffer class (colored bitmap)
GraphicsBuffer::GraphicsBuffer(Color &color, GraphicsSystem* pGraphics, bool owned) 
{
	// creates a new bitmap, sets its dimensions to the display's, and makes it the passed-in color
	SDL_SetRenderDrawColor(pGraphics->mpRenderer, color.mColor.r, color.mColor.g, color.mColor.b, color.mColor.a);
	


	mIsOwned = owned;
}

// constructor for the GraphicsBuffer class (backbuffer)
GraphicsBuffer::GraphicsBuffer(SDL_Surface* pBackBufferSurface, bool owned)
{
	mpSurface = pBackBufferSurface;
	mIsOwned = owned;

	mWidth = mpSurface->w;
	mHeight = mpSurface->h;
}

// destructor for the GraphicsBuffer class
GraphicsBuffer::~GraphicsBuffer()
{
	// destroys the bitmap if another object does not own it
	if (!mIsOwned)
	{
		SDL_FreeSurface(mpSurface);
	}
}

// accessor for mWidth
int GraphicsBuffer::getWidth()
{
	return mWidth;
}

// accessor for mHeight
int GraphicsBuffer::getHeight()
{
	return mHeight;
}