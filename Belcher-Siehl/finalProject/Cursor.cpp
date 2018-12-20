#include "Cursor.h"

#include <fstream>

using namespace std;

// constructor for the Cursor class
Cursor::Cursor()
{
	mIsInit = false;
	mIsInit = false;
}

// destructor for the Cursor class
Cursor::~Cursor()
{
	cleanup();
}

// initializes the Cursor class
void Cursor::init(string filename)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		string tempString;

		const string CURSOR = "CURSOR";

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

			pos = line.find(CURSOR);
			if (pos != string::npos)
			{
				fin >> tempString >> mLocXModifier >> mLocYModifier;

				mpGraphicsBuffer = new GraphicsBuffer(tempString, false);
				mpCursorSprite = new Sprite(mpGraphicsBuffer, DEFAULT_X, DEFAULT_Y, mpGraphicsBuffer->getWidth(), mpGraphicsBuffer->getHeight());
			}
		}

		fin.clear();
		fin.close();

		mIsInit = true;
	}
}

// cleans up the Cursor class
void Cursor::cleanup()
{
	if (!mIsCleanup)
	{
		delete mpCursorSprite;
		delete mpGraphicsBuffer;

		mIsCleanup = true;
	}
}

// draws the Cursor object
void Cursor::drawCursor(System* pSystem, int x, int y)
{
	x -= mLocXModifier;
	y += mLocYModifier;
	pSystem->getGraphics()->draw((float)x, (float)y, mpCursorSprite, DEFAULT_SCALE, true);
}

// changes the selected Button and loops if need be
void Cursor::changeSelectedButton(int numButtons, bool isUp)
{
	if (mSelectedButton == numButtons && isUp)
	{
		mSelectedButton = 0;
	}

	else if (mSelectedButton == 0 && !isUp) // change when the options menu is implemented - will have more buttons and starts at 4
	{
		mSelectedButton = numButtons;
	}

	else if (isUp)
	{
		mSelectedButton++;
	}

	else
	{
		mSelectedButton--;
	}
}