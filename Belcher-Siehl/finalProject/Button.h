#pragma once

#include "Sprite.h"
#include "GraphicsBuffer.h"
#include "System.h"
#include "Vector2D.h"

#include <Trackable.h>
#include <string>
#include <vector>

enum ScreenButtonType
{
	HUD_DISPLAY_BUTTONS = -5,
	TOP_SCORE_DISPLAY_BUTTONS = -4,
	BETWEEN_LEVELS_DISPLAY_BUTTONS = -3,
	GAME_OVER_DISPLAY_BUTTONS = -2,
	WIN_STATE_DISPLAY_BUTTONS = -1,

	TITLE_BUTTONS = 0,
	OPTIONS_BUTTONS,
	OPTIONS_SWITCHES_BUTTONS = 99
};

enum ButtonType
{
	BUTTON_PLAY_DIFFICULTY = 0,
	BUTTON_LOAD_SOUND,
	BUTTON_OPTIONS_LANGUAGE,
	BUTTON_QUIT_RETURN
};

class Button : public Trackable
{
public:
	Button(int type);
	~Button();

	void init(std::string filename, int screenType, int numLanguages);
	void cleanup();

	void drawButton(System* pSystem, int language);
	void drawButton(System* pSystem, std::string customText);
	void advanceCurrentTextString();

	void setCurrentTextString(int textString) { mCurrentTextString = textString; }

	int getLocX() { return (int)mLoc.getX(); };
	int getLocY() { return (int)mLoc.getY(); };
	int getCurrentTextString() { return mCurrentTextString; }

private:
	Font* mpButtonFont;
	Color mColor;
	Vector2D mLoc;
	
	std::vector <std::string> mButtonTextList;

	int mType;
	int mSize;
	int mTotalTextStrings;
	int mCurrentTextString;

	bool mIsInit;
	bool mIsCleanup;
};