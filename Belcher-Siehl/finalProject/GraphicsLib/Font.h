#pragma once

#include "SDL_ttf.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <string>

// the Font class
class Font : public Trackable
{
public:
	// constructors
	Font();
	Font(std::string &filename, int size);

	// destructor
	~Font();

	// accessor
	int getSize();

	// friends
	friend class GraphicsSystem;

private:
	TTF_Font* mpFont;
	int mSize;
};