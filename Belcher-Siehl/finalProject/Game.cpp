#include "Game.h"
#include "Sprite.h"
#include "GraphicsBufferManager.h"
#include <time.h>
#include "Physics.h"
#include "ScorePointsEvent.h"
#include "AddCoinsEvent.h"
#include "PlaySoundEffectEvent.h"
#include "PlayMusicEvent.h"
#include "SetPowerUpEvent.h"

#include <cassert>

#include "GraphicsBuffer.h"

#include <string>
#include <fstream>

using namespace std;

// the static Game instance
Game* Game::mpsGameInstance = NULL;

// constructor for the Game class
Game::Game() : EventListener(EventSystem::getInstance())
{
	// sets the specific data file used in the program
	mDataFile = "Assets/DataManager.txt";

	mpInputTranslator = new InputTranslator(EventSystem::getInstance());

	mpSystem = new System();

	mpTimer = new Timer;
	mpFrameTracker = new PerformanceTracker;
	mFrameCounter = 0;

	mInput = -1;
	mCanAnimate = true;

	mIsInit = false;
	mIsCleanup = false;
	mIsLooping = true;
}

// destructor for the Game class
Game::~Game()
{
	cleanup();
}

// initializes the System class and all connected classes
int Game::init()
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;
		
		const string FRAME_DIVIDER = "FRAME DIVIDER";
		const string FRAME_RATE = "FRAME RATE";
		const string DISPLAY_WIDTH = "DISPLAY WIDTH";
		const string DISPLAY_HEIGHT = "DISPLAY HEIGHT";
		const string ANIMATION_SPEED = "ANIMATION SPEED";

		fin.open(mDataFile);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return 1;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(FRAME_DIVIDER);
			if (pos != string::npos)
			{
				fin >> mFrameDivider;
			}

			pos = line.find(FRAME_RATE);
			if (pos != string::npos)
			{
				fin >> mIntendedFrameRate;
			}

			pos = line.find(DISPLAY_WIDTH);
			if (pos != string::npos)
			{
				fin >> mDisplayWidth;
			}

			pos = line.find(DISPLAY_HEIGHT);
			if (pos != string::npos)
			{
				fin >> mDisplayHeight;
			}

			pos = line.find(ANIMATION_SPEED);
			if (pos != string::npos)
			{
				fin >> mAnimationSpeed;
			}

		}

		mFrameRate = (mFrameDivider / mIntendedFrameRate);

		fin.clear();
		fin.close();
		srand((unsigned)time(NULL));

		mpSystem->init(mDisplayWidth, mDisplayHeight, mDataFile);

		mpLevelManager = new LevelManager(mDataFile, mpSystem);
		mpScreenManager = new ScreenManager(mDataFile);
		mpPermanentGameData = new PermanentGameData();
		mpSaveDataManager = new SaveDataManager();

		mpInputTranslator->init();

		mpLevelManager->init();
		mpScreenManager->init();
		mpSaveDataManager->init(mDataFile);

		// Event Listeners
		EventSystem::getInstance()->addListener(UP_MOVE_EVENT, this);
		EventSystem::getInstance()->addListener(DOWN_MOVE_EVENT, this);
		EventSystem::getInstance()->addListener(RIGHT_MOVE_EVENT, this);
		EventSystem::getInstance()->addListener(LEFT_MOVE_EVENT, this);
		EventSystem::getInstance()->addListener(START_LEVEL_EVENT, this);
		EventSystem::getInstance()->addListener(START_LEVEL_GAMEPLAY_EVENT, this);
		EventSystem::getInstance()->addListener(SCORE_POINTS_EVENT, this);
		EventSystem::getInstance()->addListener(ADD_COINS_EVENT, this);
		EventSystem::getInstance()->addListener(GAME_OVER_EVENT, this);
		EventSystem::getInstance()->addListener(LOAD_GAME_EVENT, this);

		EventSystem::getInstance()->addListener(TOGGLE_AUDIO_EVENT, this);
		EventSystem::getInstance()->addListener(PLAY_SOUND_EFFECT_EVENT, this);
		EventSystem::getInstance()->addListener(PLAY_MUSIC_EVENT, this);
		EventSystem::getInstance()->addListener(SELECT_BUTTON_EVENT, this);
		EventSystem::getInstance()->addListener(CHANGE_DIFFICULTY_EVENT, this);
		EventSystem::getInstance()->addListener(EXIT_GAME_EVENT, this);

		EventSystem::getInstance()->addListener(KILL_PLAYER_CHARACTER_EVENT, this);

		EventSystem::getInstance()->addListener(KEY_PRESS_EVENT, mpInputTranslator);
		EventSystem::getInstance()->addListener(KEY_UP_EVENT, this);

		EventSystem::getInstance()->addListener(ENVIRONMENT_MOVE_EVENT, this);

		EventSystem::getInstance()->addListener(SET_POWER_UP_EVENT, this);

		EventSystem::getInstance()->addListener(END_OF_LEVEL_EVENT, this);
		EventSystem::getInstance()->addListener(WIN_GAME_EVENT, this);

		// ensures that this initialization is not called again
		mIsInit = true;
	}

	return 1;
}

// destroys all aspects of the Game class
void Game::cleanup()
{
	if (!mIsCleanup)
	{
		mpSystem->cleanup();

		delete mpSystem;
		delete mpGraphicsBufferManager;
		delete mpInputTranslator;
		delete mpLevelManager;
		delete mpScreenManager;
		delete mpPermanentGameData;
		delete mpSaveDataManager;

		for (unsigned i = 0; i < mAnimationList.size(); i++)
		{
			delete mAnimationList.at(i);
		}

		mAnimationList.clear();

		delete mpTimer;
		delete mpFrameTracker;

		mIsCleanup = true;
	}
}

// returns the static Game instance
Game* Game::getInstance()
{
	assert(mpsGameInstance != nullptr);
	return mpsGameInstance;
}

// initializes the static Game object
void Game::initInstance()
{
	mpsGameInstance = new Game;
}

// initializes the static Game object
void Game::cleanupInstance()
{
	delete mpsGameInstance;
}

// initializes information pertaining to different levels
void Game::checkLevel()
{
	if (mpLevelManager->getOnLevel())
	{
		mpLevelManager->updateLevel();
	}

	mpScreenManager->drawScreen(mpSystem, mpLevelManager, mpPermanentGameData);
}

// receives the user's input
void Game::getInput()
{
	mpSystem->getInputSystem()->update(mpLevelManager->getOnLevel());
}

// returns the attached System
System* Game::getSystem()
{
	return mpSystem;
}

// returns the attached LevelManager
LevelManager* Game::getLevelManager()
{
	return mpLevelManager;
}

// returns the attached GraphicsBufferManager
GraphicsBufferManager* Game::getGraphicsBufferManager()
{
	return mpGraphicsBufferManager;
}

// returns the attached ScreenManager
ScreenManager* Game::getScreenManager()
{
	return mpScreenManager;
}

// the core gameplay loop
void Game::doLoop()
{
	// the main loop
	do
	{
		// start the timers used to determine the loop's frame rate
		mpFrameTracker->startTracking("Time_Tracker");
		mpTimer->start();

		// determines which Events are called based on user input
		getInput();

		// draws the background, moves the snake, and draws any powerups
		checkLevel();

		mpSystem->getGraphics()->flip();

		mpTimer->sleepUntilElapsed(mFrameRate);

		// reports the amount of time in milliseconds it takes to process a frame
		mpFrameTracker->stopTracking("Time_Tracker");

		mpFrameTracker->clearTracker("Time_Tracker");
	} while (mIsLooping);
}

// exits the gameplay loop
void Game::exitGame()
{
	mIsLooping = false;
}

// kills the player character
void Game::killPlayerCharacter()
{
	mpSystem->getAudioManager()->playMusic(DEATH);

	mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setJumpBool(false);
	mpPermanentGameData->addLives(-1);

	mpLevelManager->accessOnLevel(mpPermanentGameData->getDifficulty());

	// if the player has lives remaining, restart the level
	if (mpPermanentGameData->getLives() > 0)
	{
		mpLevelManager->getCurrentLevel()->resetLevel();
	}

	// if the player does not have lives remaining, end the game
	else
	{
		gameOver();
	}
}

// gives the player a game over and resets the game
void Game::gameOver()
{
	mpSystem->getAudioManager()->playMusic(GAMEOVER);
	mpScreenManager->setScreenType(GAME_OVER);
	mpLevelManager->resetAllLevels();
	mpLevelManager->setCurrentLevel(0);
	mpPermanentGameData->setLives(STARTING_LIVES);
}

// shows the win state
void Game::winGame()
{
	mpSystem->getAudioManager()->playMusic(WORLD_CLEAR);
	mpScreenManager->setScreenType(WIN_STATE);
	mpLevelManager->resetAllLevels();
	mpLevelManager->setCurrentLevel(0);
}

// handles Game events
void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == UP_MOVE_EVENT )
	{
		if (!mpLevelManager->getOnLevel())
		{
			mpScreenManager->getCursor()->changeSelectedButton(3, false);
		}
		else 
		{
			mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->initJump();
		}
	}

	else if (theEvent.getType() == DOWN_MOVE_EVENT)
	{

		if (!mpLevelManager->getOnLevel())
		{
			mpScreenManager->getCursor()->changeSelectedButton(3, true);
		}

	}

	else if (theEvent.getType() == LEFT_MOVE_EVENT)
	{

		// if the player is facing right then flip horizontally (over the y-axis)
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->setAnimation(MARIO_WALK * mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->getNumAnimStates() + mpPermanentGameData->getPowerUp());

		// move left if mario isnt past 0
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setMovingLeft(true);
		
	}

	else if (theEvent.getType() == RIGHT_MOVE_EVENT)
	{
		// if the player is facing left then flip horizontally (over the y-axis)
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->setAnimation(MARIO_WALK * mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->getNumAnimStates() + mpPermanentGameData->getPowerUp());

		// move right if mario isnt past center of screen
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setMovingRight(true);

	}

	else if (theEvent.getType() == KEY_UP_EVENT)
	{
		// anim switch
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->setAnimation(MARIO_IDLE * mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->getNumAnimStates() + mpPermanentGameData->getPowerUp());

		// resets speed
		mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->notMoving();
	}

	else if (theEvent.getType() == SET_POWER_UP_EVENT)
	{
		const PowerUpEvent& powerUpEvent = static_cast<const PowerUpEvent&>(theEvent);
		mpPermanentGameData->changePowerUpState(powerUpEvent.getPower());
	}

	else if (theEvent.getType() == START_LEVEL_EVENT)
	{
		if (!mpLevelManager->getGameOver() && !mpLevelManager->getWin())
		{
			mpSystem->getAudioManager()->haltMusic();
			mpScreenManager->setScreenType(BETWEEN_LEVELS);
		}
	}

	else if (theEvent.getType() == START_LEVEL_GAMEPLAY_EVENT)
	{
		mpLevelManager->initLevelLayout(mpLevelManager->getCurrentLevelNumber() - 1);
		mpSystem->getAudioManager()->playMusic(mpLevelManager->getCurrentLevel()->getLevelType());
		mpLevelManager->accessOnLevel(mpPermanentGameData->getDifficulty());
		mpLevelManager->accessStart();
	}

	else if (theEvent.getType() == SCORE_POINTS_EVENT)
	{
		const ScorePointsEvent& scorePointsEvent = static_cast<const ScorePointsEvent&>(theEvent);
		mpPermanentGameData->addScore(scorePointsEvent.getScore());
	}

	else if (theEvent.getType() == ADD_COINS_EVENT)
	{
		const AddCoinsEvent& addCoinsEvent = static_cast<const AddCoinsEvent&>(theEvent);
		mpPermanentGameData->addCoins(addCoinsEvent.getCoins());
	}

	else if (theEvent.getType() == GAME_OVER_EVENT)
	{
		mpLevelManager->accessGameOver();
	}

	else if (theEvent.getType() == WIN_GAME_EVENT)
	{
		winGame();
	}

	else if (theEvent.getType() == END_OF_LEVEL_EVENT)
	{
		bool onFlag = mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getFlagContact();
		if (!onFlag)
		{
			mpSystem->getAudioManager()->playSoundEffects(FLAGPOLE);
		}

		mpSystem->getAudioManager()->haltMusic();

		for (int i = 0; i < mpLevelManager->getCurrentLevel()->getGameObjectManager()->getListSize(); i++)
		{
			if (mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getType() == FLAG)
			{
				if (mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getLoc().getY() > mpSystem->getGraphics()->getHeight() - FLAG_HEIGHT)
				{
					mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setGroundBool(true);

					mpLevelManager->nextLevel();
				}
				else
				{
					mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setGroundBool(false);
					float marioY = mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getLoc().getY();
					float flagY = mpLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getLoc().getY();
					if (flagY > marioY)
					{
						EventSystem::getInstance()->fireEvent(ScorePointsEvent(FLAG_FALL_POINTS));
					}
				}

			}
		}
	}

	else if (theEvent.getType() == WIN_GAME_EVENT)
	{
		winGame();
	}

	else if (theEvent.getType() == LOAD_GAME_EVENT)
	{
		mpSaveDataManager->loadData(mpPermanentGameData, mpLevelManager, mpScreenManager, mpSystem->getAudioManager());
	}

	else if (theEvent.getType() == SELECT_BUTTON_EVENT)
	{
		mpScreenManager->selectButton();
	}

	else if (theEvent.getType() == PLAY_SOUND_EFFECT_EVENT)
	{
		const PlaySoundEffectEvent& playSoundEffectEvent = static_cast<const PlaySoundEffectEvent&>(theEvent);
		mpSystem->getAudioManager()->playSoundEffects(playSoundEffectEvent.getSound());
	}

	else if (theEvent.getType() == PLAY_MUSIC_EVENT)
	{
		const PlayMusicEvent& playMusicEvent = static_cast<const PlayMusicEvent&>(theEvent);
		mpSystem->getAudioManager()->playMusic(playMusicEvent.getMusic());
	}

	else if (theEvent.getType() == TOGGLE_AUDIO_EVENT)
	{
		mpSystem->getAudioManager()->toggleSound();
	}

	else if (theEvent.getType() == CHANGE_DIFFICULTY_EVENT)
	{
		mpPermanentGameData->nextDifficulty();
	}

	else if (theEvent.getType() == KILL_PLAYER_CHARACTER_EVENT)
	{
		killPlayerCharacter();
	}

	else if (theEvent.getType() == EXIT_GAME_EVENT)
	{
		mpSaveDataManager->saveData(mpPermanentGameData, mpLevelManager, mpScreenManager, mpSystem->getAudioManager());
		mIsLooping = false;
	}
}