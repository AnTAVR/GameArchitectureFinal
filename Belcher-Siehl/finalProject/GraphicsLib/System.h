#pragma once

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "AudioManager.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <SDL.h>

#include <string>

enum DrawPos
{
	DEFAULT_X = 0,
	DEFAULT_Y = 0,
	DEFAULT_SCALE = 1
};

class System : public Trackable
{
public:
	// constructor and destructor
	System();
	~System();

	// initializes all aspects of the System class
	int init(int displayWidth, int displayHeight, std::string filename);

	// destroys all aspects of the System class
	void cleanup();

	GraphicsSystem* getGraphics();
	InputSystem* getInputSystem();
	AudioManager* getAudioManager() { return mpAudioManager; }

private:
	// determine if the class is initialized or cleaned up
	bool mIsInit;
	bool mIsCleanup;

	// determine if a button can be pressed
	bool mButtonPress;
	bool mMousePress;

	GraphicsSystem* mpGraphics;
	InputSystem* mpInputSystem;
	AudioManager* mpAudioManager;
};