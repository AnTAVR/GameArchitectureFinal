#include "Language.h"
#include <fstream>

using namespace std;

// constructor for the Language class
Language::Language()
{
	mIsInit = false;
	mCurrentLanguage = 0;
}

// destructor for the Language class
Language::~Language()
{

}

// initializes all variables in the Language class
void Language::init(string filename)
{
	if (!mIsInit)
	{
		ifstream fin;
		size_t pos;
		string line;

		const string NUM_LANGUAGES = "NUM LANGUAGES";

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

			pos = line.find(NUM_LANGUAGES);
			if (pos != string::npos)
			{
				fin >> mNumLanguages;
			}
		}

		fin.clear();
		fin.close();
	}
}

// moves to the next language in the list
void Language::nextLanguage()
{
	if (mCurrentLanguage >= (mNumLanguages - 1))
	{
		mCurrentLanguage = 0;
	}

	else
	{
		mCurrentLanguage++;
	}
}