#include "System.h"

#include <iostream>

using namespace std;

// constructor for the System class
System::System()
{
	mpGraphics = new GraphicsSystem();
	mpInputSystem = new InputSystem();

	mIsInit = false;
	mIsCleanup = false;
	mButtonPress = true;
	mMousePress = true;
}

// destructor for the System class
System::~System()
{
	cleanup();
}

// initializes the System class and all connected classes
int System::init(int displayWidth, int displayHeight, string filename)
{
	if (!mIsInit)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			cout << "error initting SDL" << endl;
			return 1;
		}

		if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		if (TTF_Init() != 0)
		{
			cout << "error initting TTF" << endl;
			return 1;
		}

		mpGraphics->init(displayWidth, displayHeight);
		mpInputSystem->init();

		mpAudioManager = new AudioManager();
		mpAudioManager->init(filename);
		mIsInit = true;
	}

	return 1;
}

// destroys all aspects of the System class
void System::cleanup()
{
	if (!mIsCleanup)
	{
		delete mpGraphics;
		delete mpInputSystem;
		delete mpAudioManager;
		mIsCleanup = true;
	}
}

// get mpGraphics
GraphicsSystem* System::getGraphics()
{
	return mpGraphics;
}

// get mpInputSystem
InputSystem* System::getInputSystem()
{
	return mpInputSystem;
}