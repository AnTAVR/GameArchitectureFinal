#include "SaveDataManager.h"

#include <fstream>

using namespace std;

// constructor for the SaveDataManager class
SaveDataManager::SaveDataManager()
{

}

// destructor for the SaveDataManager class
SaveDataManager::~SaveDataManager()
{

}

// initializes data in the SaveDataManager class
void SaveDataManager::init(string filename)
{
	ifstream fin;
	size_t pos;
	string line;

	const string SAVE_FILE = "SAVE FILE";
	const string CONTAINS_DATA = "CONTAINS DATA";

	fin.open(filename);

	if (fin.fail())
	{
		cout << "data retrieval process failed" << endl;
		return;
	}

	// obtains the SaveDataManager file's name
	while (!fin.eof())
	{
		getline(fin, line);

		pos = line.find(SAVE_FILE);
		if (pos != string::npos)
		{
			fin >> mSaveDataFile;
		}
	}

	fin.clear();
	fin.close();

	fin.open(mSaveDataFile);

	if (fin.fail())
	{
		cout << "NO SAVE FILE" << endl;
		mHasContent = false;
	}

	else
	{
		mHasContent = true;
	}

	fin.clear();
	fin.close();
}

// saves data into the save file
void SaveDataManager::saveData(PermanentGameData* pPermanentGameData, LevelManager* pLevelManager, ScreenManager* pScreenManager, AudioManager* pAudioManager)
{
	ofstream fout;

	fout.open(mSaveDataFile);

	if (fout.fail())
	{
		cout << "data retrieval process failed" << endl;
		return;
	}

	// saves information
	else
	{
		// outputs data relating to Permanent Game Data, such as the player's score and coin count
		fout << "// PERMANENT GAME DATA" << endl << endl;
		fout << "HIGH SCORE" << endl << pPermanentGameData->getHighScore() << endl << endl;
		fout << "CURRENT SCORE" << endl << pPermanentGameData->getScore() << endl << endl;
		fout << "COINS" << endl << pPermanentGameData->getCoins() << endl << endl;
		fout << "LIVES" << endl << pPermanentGameData->getLives() << endl << endl;
		fout << "POWERUP" << endl << pPermanentGameData->getPowerUp() << endl << endl;
		fout << "DIFFICULTY" << endl << pPermanentGameData->getDifficulty() << endl << endl;
		fout << "--------------------------------------------------" << endl << endl;

		// outputs data relating to the current level the player is on and whether or not they are playing
		fout << "// LEVEL DATA" << endl << endl;
		fout << "CURRENT LEVEL" << endl << pLevelManager->getCurrentLevelOnLoad() << endl << endl;
		fout << "ON LEVEL" << endl << pLevelManager->getOnLevel() << endl << endl;
		fout << "LEVEL TIMER" << endl << pLevelManager->getCurrentLevel()->getTimer() << endl << endl;
		fout << "--------------------------------------------------" << endl << endl;

		// outputs data relating to the player character, such as their current location and whether or not they are jumping
		fout << "// PLAYER CHARACTER DATA" << endl << endl;
		fout << "POSITION" << endl << (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getLoc().getX() << " " << (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getLoc().getY() << endl << endl;
		fout << "JUMPING" << endl << pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getJumpBool() << endl << endl;
		fout << "GROUNDED" << endl << pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getGroundedBool() << endl << endl;
		fout << "CAN MOVE" << endl << pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getCanMove() << endl << endl;
		fout << "ANIMATION" << endl << pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->getCurrentAnimation() << endl << endl;
		fout << "CURRENT ANIMATION FRAME" << endl << pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->getCurrentFrame() << endl << endl;
		fout << "--------------------------------------------------" << endl << endl;

		// outputs data relating to the screen
		fout << "// SCREEN DATA" << endl << endl;
		fout << "SCREEN TYPE" << endl << pScreenManager->getScreenType() << endl << endl;
		fout << "TIMER BETWEEN SCREENS" << endl << pScreenManager->getCountdownTimer() << endl << endl;
		fout << "SELECTED BUTTON" << endl << pScreenManager->getCursor()->getSelectedButton() << endl << endl;
		fout << "LANGUAGE" << endl << pScreenManager->getLanguage()->getLanguage() << endl << endl;
		fout << "OPTIONS SWITCHES TEXT STRINGS" << endl;
		for (int i = 0; i < pScreenManager->getOptionsSwitchSize(); i++)
		{
			fout << pScreenManager->getOptionsSwitch(i)->getCurrentTextString() << endl;
		}
		fout << endl;
		fout << "--------------------------------------------------" << endl << endl;

		// outputs data relating to the game's audio, such as which song, if any, is currently playing
		fout << "// AUDIO DATA" << endl << endl;
		fout << "MUSIC INDEX" << endl << pAudioManager->getLastMusic() << endl << endl;
		fout << "--------------------------------------------------" << endl << endl;

		// outputs data relating to the GameObjects contained in the current level, including their current position
		fout << "// GAME OBJECT MANAGER DATA" << endl << endl;
		fout << "GAME OBJECTS" << endl;
		for (int i = 1; i < pLevelManager->getCurrentLevel()->getGameObjectManager()->getListSize(); i++)
		{
			fout	<< (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getLoc().getX() << " "
					<< (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getLoc().getY() << " "
					<< (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getExists() << " "
					<< (int)pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->getDestroyed() << endl;
		}
		fout << endl;
	}

	fout.clear();
	fout.close();
}

// loads in data from the save file
void SaveDataManager::loadData(PermanentGameData* pPermanentGameData, LevelManager* pLevelManager, ScreenManager* pScreenManager, AudioManager* pAudioManager)
{
	if (mHasContent)
	{
		ifstream fin;
		size_t pos;
		string line;

		int tempX, tempY, tempMisc;
		bool tempBool, secondTempBool;

		const string HIGH_SCORE = "HIGH SCORE";
		const string CURRENT_SCORE = "CURRENT SCORE";
		const string COINS = "COINS";
		const string LIVES = "LIVES";
		const string POWERUP = "POWERUP";
		const string DIFFICULTY = "DIFFICULTY";

		const string CURRENT_LEVEL = "CURRENT LEVEL";
		const string ON_LEVEL = "ON LEVEL";
		const string TIMER = "LEVEL TIMER";

		const string POSITION = "POSITION";
		const string JUMPING = "JUMPING";
		const string GROUNDED = "GROUNDED";
		const string CAN_MOVE = "CAN MOVE";
		const string ANIMATION = "ANIMATION";
		const string CURRENT_ANIMATION_FRAME = "CURRENT ANIMATION FRAME";

		const string MUSIC_INDEX = "MUSIC INDEX";

		const string SCREEN_TYPE = "SCREEN TYPE";
		const string TIMER_BETWEEN_SCREENS = "TIMER BETWEEN SCREENS";
		const string SELECTED_BUTTON = "SELECTED BUTTON";
		const string LANGUAGE = "LANGUAGE";
		const string OPTIONS_SWITCHES_TEXT_STRINGS = "OPTIONS SWITCHES TEXT STRINGS";

		const string GAME_OBJECTS = "GAME OBJECTS";

		fin.open(mSaveDataFile);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// loads information
		while (!fin.eof())
		{
			getline(fin, line);

			// sets values pertaining to the overall game
			pos = line.find(HIGH_SCORE);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setHighScore(tempMisc);
			}

			pos = line.find(CURRENT_SCORE);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setScore(tempMisc);
			}

			pos = line.find(COINS);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setCoins(tempMisc);
			}

			pos = line.find(LIVES);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setLives(tempMisc);
			}

			pos = line.find(POWERUP);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setPowerUp(tempMisc);
			}

			pos = line.find(DIFFICULTY);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pPermanentGameData->setDifficulty(tempMisc);
			}

			// sets data pertaining to the current level
			pos = line.find(CURRENT_LEVEL);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pLevelManager->setCurrentLevel(tempMisc);
			}

			pos = line.find(ON_LEVEL);
			if (pos != string::npos)
			{
				fin >> tempBool;
				if (tempBool)
				{
					pLevelManager->accessOnLevelOnLoad();
					pLevelManager->accessStart();

					if (pLevelManager->getOnLevel())
					{
						pLevelManager->initLevelLayout(pLevelManager->getCurrentLevelNumber() - 1);
					}
				}
			}

			pos = line.find(TIMER);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pLevelManager->getCurrentLevel()->setTimerOnLoad(tempMisc);
			}

			// sets data pertaining to the player character
			pos = line.find(POSITION);
			if (pos != string::npos)
			{
				fin >> tempX >> tempY;

				pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setLocX((float)tempX);
				pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setLocY((float)tempY);
			}

			pos = line.find(GROUNDED);
			if (pos != string::npos)
			{
				fin >> tempBool;
				pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setGroundBool(tempBool);
			}

			pos = line.find(CAN_MOVE);
			if (pos != string::npos)
			{
				fin >> tempBool;
				pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->setCanMoveBoolOnLoad(tempBool);
			}

			pos = line.find(ANIMATION);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(MARIO)->getAnimator()->setAnimation(tempMisc);
			}

			// sets data pertaining the screen
			pos = line.find(SCREEN_TYPE);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pScreenManager->setScreenType(tempMisc);
			}

			pos = line.find(SELECTED_BUTTON);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pScreenManager->getCursor()->setSelectedButton(tempMisc);
			}

			pos = line.find(LANGUAGE);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				pScreenManager->getLanguage()->setLanguage(tempMisc);
			}

			pos = line.find(OPTIONS_SWITCHES_TEXT_STRINGS);
			if (pos != string::npos)
			{
				for (int i = 0; i < pScreenManager->getOptionsSwitchSize(); i++)
				{
					fin >> tempMisc;
					pScreenManager->getOptionsSwitch(i)->setCurrentTextString(tempMisc);

					getline(fin, line);
				}
			}

			// sets data pertaining to the game's audio
			pos = line.find(MUSIC_INDEX);
			if (pos != string::npos)
			{
				fin >> tempMisc;
				if (tempMisc > -1)
				{
					pAudioManager->playMusic(tempMisc);
				}

				else
				{
					pAudioManager->haltMusic();
				}
			}

			// sets data pertaining to other game objects on the screen
			pos = line.find(GAME_OBJECTS);
			if (pos != string::npos)
			{
				for (int i = 1; i < pLevelManager->getCurrentLevel()->getGameObjectManager()->getListSize(); i++)
				{
					fin >> tempX >> tempY >> tempBool >> secondTempBool;
					pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setLocX((float)tempX);
					pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setLocY((float)tempY);
					pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setExists(tempBool);
					pLevelManager->getCurrentLevel()->getGameObjectManager()->getObject(i)->setIsDestroyed(secondTempBool);

					getline(fin, line);
				}
			}
		}

		fin.clear();
		fin.close();
	}
}