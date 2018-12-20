#include "Button.h"

#include <fstream>

using namespace std;

// constructor for the Button class
Button::Button(int type)
{
	mType = type;
	mIsInit = false;
	mIsCleanup = false;
	mCurrentTextString = 0;
}

// destructor for the Button class
Button::~Button()
{
	cleanup();
}

// initializes all variables in the Button class
void Button::init(string filename, int screenType, int numLanguages)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		float x, y;

		string tempString;
		int tempSize;
		int r, g, b;

		const string TITLE_FONT = "TITLE FONT";
		const string HUD_FONT = "HUD FONT";
		const string TITLE_TEXT_COLOR = "TITLE TEXT COLOR";
		const string HUD_TEXT_COLOR = "HUD TEXT COLOR";

		const string HUD_DISPLAY_BUTTON = "HUD DISPLAY " + to_string(mType);
		const string TOP_SCORE_BUTTON = "TOP SCORE BUTTON " + to_string(mType);
		const string BETWEEN_LEVELS_BUTTON = "BETWEEN LEVELS BUTTON " + to_string(mType);
		const string TITLE_BUTTON = "TITLE BUTTON " + to_string(mType);
		const string OPTIONS_BUTTON = "OPTIONS BUTTON " + to_string(mType);
		const string OPTIONS_SWITCH_BUTTON = "OPTIONS SWITCH " + to_string(mType);
		const string GAME_OVER_BUTTON = "GAME OVER BUTTON " + to_string(mType);
		const string WIN_STATE_BUTTON = "WIN STATE BUTTON " + to_string(mType);

		fin.open(filename);

		if (fin.fail())
		{
			cout << "data retrieval process failed" << endl;
			return;
		}

		// obtains multiple variables from the data file
		while (!fin.eof())
		{
			getline(fin, line);

			pos = line.find(TITLE_FONT);
			if (pos != string::npos && screenType != HUD_DISPLAY_BUTTONS && screenType != BETWEEN_LEVELS_DISPLAY_BUTTONS && screenType != GAME_OVER_DISPLAY_BUTTONS && screenType != WIN_STATE_DISPLAY_BUTTONS)
			{
				fin >> tempString >> tempSize;

				Font* tempFont = new Font(tempString, tempSize);
				mpButtonFont = tempFont;
			}

			pos = line.find(HUD_FONT);
			if (pos != string::npos && screenType != TITLE_BUTTONS && screenType != OPTIONS_BUTTONS && screenType != OPTIONS_SWITCHES_BUTTONS && screenType != TOP_SCORE_DISPLAY_BUTTONS)
			{
				fin >> tempString >> tempSize;

				Font* tempFont = new Font(tempString, tempSize);
				mpButtonFont = tempFont;
			}

			pos = line.find(TITLE_TEXT_COLOR);
			if (pos != string::npos && screenType != HUD_DISPLAY_BUTTONS && screenType != BETWEEN_LEVELS_DISPLAY_BUTTONS && screenType != GAME_OVER_DISPLAY_BUTTONS && screenType != WIN_STATE_DISPLAY_BUTTONS)
			{
				fin >> r >> g >> b;

				mColor = Color(r, g, b);
			}

			pos = line.find(HUD_TEXT_COLOR);
			if (pos != string::npos && screenType != TITLE_BUTTONS && screenType != OPTIONS_BUTTONS && screenType != OPTIONS_SWITCHES_BUTTONS && screenType != TOP_SCORE_DISPLAY_BUTTONS)
			{
				fin >> r >> g >> b;

				mColor = Color(r, g, b);
			}

			pos = line.find(HUD_DISPLAY_BUTTON);
			if (pos != string::npos && screenType == HUD_DISPLAY_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(TOP_SCORE_BUTTON);
			if (pos != string::npos && screenType == TOP_SCORE_DISPLAY_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(BETWEEN_LEVELS_BUTTON);
			if (pos != string::npos && screenType == BETWEEN_LEVELS_DISPLAY_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(TITLE_BUTTON);
			if (pos != string::npos && screenType == TITLE_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(OPTIONS_BUTTON);
			if (pos != string::npos && screenType == OPTIONS_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(OPTIONS_SWITCH_BUTTON);
			if (pos != string::npos && screenType == OPTIONS_SWITCHES_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(GAME_OVER_BUTTON);
			if (pos != string::npos && screenType == GAME_OVER_DISPLAY_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}

			pos = line.find(WIN_STATE_BUTTON);
			if (pos != string::npos && screenType == WIN_STATE_DISPLAY_BUTTONS)
			{
				fin >> x >> y >> mTotalTextStrings;

				mLoc.setX(x);
				mLoc.setY(y);

				getline(fin, tempString);

				for (int i = 0; i < numLanguages * mTotalTextStrings; i++)
				{
					getline(fin, tempString);
					mButtonTextList.push_back(tempString);
				}
			}
		}

		fin.clear();
		fin.close();

		mIsInit = true;
	}
}

// clear all values in the Button class
void Button::cleanup()
{
	if (!mIsCleanup)
	{
		delete mpButtonFont;

		mIsCleanup = true;
	}
}

// draws all Button objects if applicable
void Button::drawButton(System* pSystem, int language)
{
	pSystem->getGraphics()->writeText(mLoc.getX(), mLoc.getY(), mpButtonFont, mColor, mButtonTextList.at(language * mTotalTextStrings + mCurrentTextString));
}

// draws all Button objects if applicable
void Button::drawButton(System* pSystem, string customText)
{
	pSystem->getGraphics()->writeText(mLoc.getX(), mLoc.getY(), mpButtonFont, mColor, customText);
}

// advances the text string for cases where the buttons have multiple types
void Button::advanceCurrentTextString()
{
	if (mCurrentTextString >= (mTotalTextStrings - 1))
	{
		mCurrentTextString = 0;
	}

	else
	{
		mCurrentTextString++;
	}
}