#include "Level.h"
#include "Game.h"
#include "Color.h"

#include "EventSystem.h"
#include "Event.h"
#include "PlayMusicEvent.h"
#include "KillPlayerCharacterEvent.h"

#include <fstream>

using namespace std;

// constructor for the Level class
Level::Level(System* pSystem, string filename, int levelNum)
{
	mDataFile = filename;
	mpSystem = pSystem;
	mpGridManager = new GridManager(filename);
	mpGameObjectManager = new GameObjectManager(filename);

	mLevelNum = levelNum;
	mTimerCounter = 0;

	mIsInit = false;
	mIsClear = false;
}

// destructor for the Level class
Level::~Level()
{
	clear();
}

// initializes the Level class
void Level::init()
{
	if (!mIsInit)
	{
		// initializes the grid used in this specific level
		mpGridManager->init(mpSystem->getGraphics()->getWidth(), mpSystem->getGraphics()->getHeight());
		mpGameObjectManager->init();

		// variables used for reading in from the file
		ifstream fin;
		size_t pos;
		string line;
		string backgroundBufferFile;

		int tempDifficulty;

		// creates the strings for each header object based on the current level
		const string LEVEL_LAYOUT_FILE = "LEVEL LAYOUT DATA FILE";
		const string GAME_WORLD = "GAME WORLD " + to_string(mLevelNum);
		const string WORLD_LEVEL = "WORLD LEVEL " + to_string(mLevelNum);
		const string LEVEL_TYPE = "LEVEL TYPE " + to_string(mLevelNum);
		const string LEVEL_WIDTH = "LEVEL WIDTH " + to_string(mLevelNum);
		const string LEVEL_HEIGHT = "LEVEL HEIGHT " + to_string(mLevelNum);
		const string LEVEL_TIME_LIMIT = "LEVEL TIME LIMIT " + to_string(mLevelNum);
		const string DIFFICULTIES = "DIFFICULTIES";
		const string BACKGROUND_BUFFER = "BACKGROUND BUFFER " + to_string(mLevelNum);

		fin.open(mDataFile);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(LEVEL_LAYOUT_FILE);
			if (pos != string::npos)
			{
				fin >> mLevelLayoutFile;
			}

			pos = line.find(DIFFICULTIES);
			if (pos != string::npos)
			{
				fin >> tempDifficulty;
			}

			pos = line.find(GAME_WORLD);
			if (pos != string::npos)
			{
				fin >> mWorld;
			}
			
			pos = line.find(WORLD_LEVEL);
			if (pos != string::npos)
			{
				fin >> mLevel;
			}

			pos = line.find(LEVEL_TYPE);
			if (pos != string::npos)
			{
				fin >> mLevelType;
			}

			pos = line.find(LEVEL_WIDTH);
			if (pos != string::npos)
			{
				fin >> mWidth;
			}

			pos = line.find(LEVEL_HEIGHT);
			if (pos != string::npos)
			{
				fin >> mHeight;
			}

			pos = line.find(LEVEL_TIME_LIMIT);
			if (pos != string::npos)
			{
				for (int i = 0; i < tempDifficulty; i++)
				{
					int temp;
					fin >> temp;
					mTimerDifficultyList.push_back(temp);
					getline(fin, line);
				}
			}

			// finds and uploads the file for the background
			pos = line.find(BACKGROUND_BUFFER);
			if (pos != string::npos)
			{
				fin >> backgroundBufferFile;
				mpBackground = new GraphicsBuffer(backgroundBufferFile, false);
			}
		}

		fin.clear();
		fin.close();

		mIsInit = true;
	}
}

// initializes all values in the level's layout
void Level::initLayout()
{
	if (!mIsLayoutInit)
	{
		// variables used for reading in from the file
		ifstream fin;
		size_t pos;
		string line;

		// creates the strings for each header object based on the current level
		const string LAYOUT = "LAYOUT " + to_string(mLevelNum);

		fin.open(mLevelLayoutFile);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			// creates the level layout based on the "image" in the file
			pos = line.find(LAYOUT);

			if (pos != string::npos && mpBackground != NULL)
			{
				// create level layout
				char input;

				// replace 300 with the actual size of the grid
				for (size_t i = 0; i < (unsigned)(mWidth * mHeight); i++)
				{
					fin.get(input);

					if (i % mWidth == 0 && i != 0)
					{
						fin.get(input);
					}

					if (input == 'B')
					{
						mpLevelSprite = new Sprite(mpBackground, DEFAULT_X, DEFAULT_Y);
						continue;
					}

					if (input == 'G')
					{
						mpGameObjectManager->addGameObject(GOOMBA, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == 'O')
					{
						mpGameObjectManager->addGameObject(COIN, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == 'X')
					{
						mpGameObjectManager->addGameObject(GROUND, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '+')
					{
						mpGameObjectManager->addGameObject(SOLID_BLOCK, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == 'R')
					{
						mpGameObjectManager->addGameObject(BRICK, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '?')
					{
						mpGameObjectManager->addGameObject(QUESTION_MARK_BLOCK, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '|')
					{
						mpGameObjectManager->addGameObject(FLAG_POLE, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '.')
					{
						mpGameObjectManager->addGameObject(FLAG_POLE_TOP, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '<')
					{
						mpGameObjectManager->addGameObject(FLAG, Vector2D(getXPos(i) + 36, getYPos(i)), true);
						continue;
					}

					if (input == '}')
					{
						mpGameObjectManager->addGameObject(PIPE_BODY_LEFT, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '{')
					{
						mpGameObjectManager->addGameObject(PIPE_BODY_RIGHT, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == '[')
					{
						mpGameObjectManager->addGameObject(PIPE_TOP_LEFT, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}

					if (input == ']')
					{
						mpGameObjectManager->addGameObject(PIPE_TOP_RIGHT, Vector2D(getXPos(i), getYPos(i)), true);
						continue;
					}
				}
			}
		}

		fin.clear();
		fin.close();

		mIsLayoutInit = true;
	}
}

// clears the Level class
void Level::clear()
{
	if (!mIsClear)
	{
		delete mpGridManager;

		delete mpBackground;

		delete mpLevelSprite;
		delete mpGameObjectManager;

		for (unsigned i = 0; i < mLevelSpritesList.size(); i++)
		{
			delete mLevelSpritesList.at(i);
		}

		mLevelSpritesList.clear();

		mIsClear = true;
	}
}

// draws the level's background, any existing powerups, and the snake
void Level::drawLevel()
{
	mpSystem->getGraphics()->draw(DEFAULT_X, DEFAULT_Y, mpLevelSprite, 1, true);

	mpGameObjectManager->update();

	if (mpGameObjectManager->getObject(MARIO)->onRightScreen() && mpGameObjectManager->getObject(MARIO)->getRightMoving())
	{
		for (int i = 1; i < mpGameObjectManager->getListSize(); i++)
		{
			mpGameObjectManager->getObject(i)->getPhysics().setCurrentSpeed(mpGameObjectManager->getObject(i)->getPhysics().getMaxSpeed());
			mpGameObjectManager->getObject(i)->moveScreen();
		}
	}

	mpGameObjectManager->draw(mpSystem->getGraphics());

}

// lowers the time on the timer and kills the player if it hits 0
void Level::decreaseTimer()
{
	if (mTimerCounter >= TIMER_FRAMES)
	{
		mTimerCounter = 0;
		mTimer--;

		if (mTimer == 99)
		{
			EventSystem::getInstance()->fireEvent(PlayMusicEvent(mLevelType + 1));
		}

		if (mTimer <= 0)
		{
			mTimer = 0;
			EventSystem::getInstance()->fireEvent(KillPlayerCharacterEvent());
		}
	}

	mTimerCounter++;
}

// reset all GameObject parameters in the current level
void Level::resetLevel()
{
	for (int i = 0; i < mpGameObjectManager->getListSize(); i++)
	{
		mpGameObjectManager->getObject(i)->setLocX((float)mpGameObjectManager->getObject(i)->getStartingX());
		mpGameObjectManager->getObject(i)->setLocY((float)mpGameObjectManager->getObject(i)->getStartingY());
		mpGameObjectManager->getObject(i)->setIsDestroyed(false);
		mpGameObjectManager->getObject(i)->setGroundBool(true);
	}
}

// returns the GridManager used for the current Level
GridManager* Level::getGridManager()
{
	return mpGridManager;
}

// returns the X position
int Level::getXPos(int index)
{
	return (index % mWidth) * mpGridManager->getGridScale();
}

// returns the Y position
int Level::getYPos(int index)
{
	return (index / mWidth) * mpGridManager->getGridScale();
}