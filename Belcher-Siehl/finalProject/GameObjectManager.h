#pragma once

#include <Trackable.h>
#include "GameObject.h"

#include <vector>
#include <string>
#include <Vector2D.h>

class GameObjectManager : public Trackable
{
public:
	GameObjectManager(std::string filename);
	~GameObjectManager();

	void init();
	void cleanup();

	void update();
	void draw(GraphicsSystem* pSystem);

	void addGameObject(int objectType, Vector2D loc, bool exists);
	void removeGameObject();

	GameObject* getObject(int objNum) { return mGameObjectList.at(objNum); }
	int getListSize() { return mGameObjectList.size(); }

private:
	std::vector <GameObject*> mGameObjectList;
	std::string mDataFile;

	bool mIsInit;
	bool mIsCleanup;
};