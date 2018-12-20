#pragma once

#include <Trackable.h>

#include <string>

enum Languages
{
	ENGLISH = 0,
	SPANISH,
	DEAN
};

class Language : public Trackable
{
public:
	Language();
	~Language();

	void init(std::string filename);

	void nextLanguage();

	void setLanguage(int language) { mCurrentLanguage = language; }

	int getLanguage() { return mCurrentLanguage; };
	int getNumLanguages() { return mNumLanguages; };

private:
	int mNumLanguages;
	int mCurrentLanguage;

	bool mIsInit;
};