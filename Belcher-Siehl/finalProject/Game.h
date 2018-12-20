#pragma once

#include "System.h"
#include "InputTranslator.h"
#include "Animation.h"
#include "LevelManager.h"
#include "ScreenManager.h"
#include "PermanentGameData.h"
#include "SaveDataManager.h"

#include <vector>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

class GraphicsBuffer;
class GraphicsBufferManager;

class Game : public EventListener
{
public:
	// functions pertaining to the static instance
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	// initializes the Game class
	int init();

	// destroys the Game class
	void cleanup();

	// performs the core gameplay loop
	void doLoop();

	// ends the gameplay loop
	void exitGame();

	// kills the player and restarts the current level
	void killPlayerCharacter();
	void gameOver();
	void winGame();

	// updates information regarding the current level
	void checkLevel();

	// obtains the user's input
	void getInput();

	// returns various attached items
	System* getSystem();
	LevelManager* getLevelManager();
	GraphicsBufferManager* getGraphicsBufferManager();
	ScreenManager* getScreenManager();
	PermanentGameData* getPermanentGameData() { return mpPermanentGameData; }

	// handles event information
	void handleEvent(const Event& theEvent);

private:
	// constructor and destructor
	Game();
	~Game();

	// static instance
	static Game* mpsGameInstance;

	// System pointer and GraphicsBuffer pointers used to hold graphical information
	System* mpSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	InputTranslator* mpInputTranslator;
	LevelManager* mpLevelManager;
	ScreenManager* mpScreenManager;
	PermanentGameData* mpPermanentGameData;
	SaveDataManager* mpSaveDataManager;

	Timer* mpTimer;						// determines the length of each frame
	PerformanceTracker* mpFrameTracker;	// checks the length of each frame

	std::string mDataFile;

	int mFrameCounter;		// the frame used to draw the animation
	int mAnimationSpeed;	// the speed at which the animation runs

	int mDisplayWidth;
	int mDisplayHeight;
	int mIntendedFrameRate;

	float mFrameDivider;
	float mFrameRate;

	// determines whether or not certain functions will play
	int mInput;
	bool mCanAnimate;

	// determines if the Game object is initialized or cleaned up
	bool mIsInit;
	bool mIsCleanup;
	bool mIsLooping;

	// the list comprising all animations
	std::vector <Animation*> mAnimationList;
};
