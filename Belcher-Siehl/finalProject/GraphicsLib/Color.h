#pragma once

#include <SDL.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

// the Color class
class Color : public Trackable 
{
public:
	// constructors
	Color();
	Color(int r, int g, int b);

	// destructor
	~Color();

	// friends
	friend class GraphicsBuffer;
	friend class GraphicsSystem;

private:
	SDL_Color mColor;
};