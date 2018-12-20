#pragma once

#include "Vector2D.h"
#include <MemoryTracker.h>
#include <PerformanceTracker.h>

#include <SDL.h>

#include <string>

class EventSystem;

// the InputSystem class
class InputSystem : public Trackable
{
public:
	// constructor and destructor
	InputSystem();
	~InputSystem();

	// initializer
	void init();

	// cleaner
	void cleanup();

	// updates the program to determine whether or not has obtained input
	void update(bool onLevel);

private:
	bool mIsInit;
	bool mIsCleanup;

	SDL_Event mEvent;
};