#include "Font.h"

#include <string>

using namespace std;

// default constructor for the Font class
Font::Font()
{
	mpFont = NULL;
	mSize = 0;
}

// constructor for the Font class
Font::Font(string &filename, int size)
{
	mpFont = TTF_OpenFont(("Assets\\" + filename).c_str(), size);

	if (mpFont == NULL)
	{
		cout << "YEEE" << endl;
	}

	mSize = size;
}

// destructor for the Font class
Font::~Font()
{
	TTF_CloseFont(mpFont);
	mpFont = NULL;
}

// accessor for mSize
int Font::getSize()
{
	return mSize;
}