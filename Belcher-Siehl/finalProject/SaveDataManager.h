#pragma once

#include <Trackable.h>
#include "PermanentGameData.h"
#include "LevelManager.h"
#include "ScreenManager.h"
#include "AudioManager.h"

#include <string>

class SaveDataManager : public Trackable
{
public:
	SaveDataManager();
	~SaveDataManager();

	void init(std::string filename);

	void saveData(PermanentGameData* pPermanentGameData, LevelManager* pLevelManager, ScreenManager* pScreenManager, AudioManager* pAudioManager);
	void loadData(PermanentGameData* pPermanentGameData, LevelManager* pLevelManager, ScreenManager* pScreenManager, AudioManager* pAudioManager);

private:
	bool mHasContent;
	std::string mSaveDataFile;
};