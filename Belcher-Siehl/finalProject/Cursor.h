#pragma once

#include <Trackable.h>
#include "System.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

#include <string>

class Cursor : public Trackable
{
public:
	Cursor();
	~Cursor();

	void init(std::string filename);
	void cleanup();

	void drawCursor(System* pSystem, int x, int y);

	void changeSelectedButton(int numButtons, bool isUp);

	void setSelectedButton(int mButton) { mSelectedButton = mButton; };
	int getSelectedButton() { return mSelectedButton; };

private:
	Sprite* mpCursorSprite;
	GraphicsBuffer* mpGraphicsBuffer;

	int mSelectedButton;
	int mLocXModifier;
	int mLocYModifier;

	bool mIsInit;
	bool mIsCleanup;
};