#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <string>

class GraphicsSystem;
class Color;

// the GraphicsBuffer class
class GraphicsBuffer : public Trackable
{
public:
	// constructor
	GraphicsBuffer(std::string filename, bool owned);
	GraphicsBuffer(Color &color, GraphicsSystem* pGraphics, bool owned);

	// destructor
	~GraphicsBuffer();

	// accessors
	int getWidth();
	int getHeight();

private:
	friend class GraphicsSystem;
	
	GraphicsBuffer(SDL_Surface* pSurface, bool owned);

	int mWidth;
	int mHeight;

	SDL_Surface* mpSurface;
	bool mIsOwned;
};