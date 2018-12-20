#include "GameObjectAnimator.h"
#include "GameObject.h"
#include "GraphicsBuffer.h"
#include <fstream>

using namespace std;

// constructor for the GameObjectAnimator class
GameObjectAnimator::GameObjectAnimator(string filename)
{
	mDataFile = filename;

	mIsInit = false;
	mIsCleanup = false;
}

// destructor for the GameObjectAnimator class
GameObjectAnimator::~GameObjectAnimator()
{
	cleanup();
}

// initializes information for the GameObjectAnimator class
void GameObjectAnimator::init(int objectType)
{
	if (!mIsInit)
	{
		// variables used for reading in from the file
		ifstream fin;
		size_t pos;
		string line;

		string objectTemp;
		int sheetHeight, sheetWidth, spriteHeight, spriteWidth, numSprites;

		// creates animations for the Mario character type
		if (objectType == MARIO)
		{
			const string MARIO_ANIM_SPEED = "MARIO ANIM SPEED";
			const string NUM_MARIO_ANIM_STATES = "NUM MARIO ANIM STATES";
			const string MARIO_SPRITE_SIZE = "MARIO SPRITE SIZE";

			const string MARIO_IDLE_ANIM = "MARIO IDLE ANIM";
			const string MARIO_WALK_ANIM = "MARIO WALK ANIM";
			const string MARIO_JUMP_ANIM = "MARIO JUMP ANIM";

			// other animations
			// open file, load in animations, cut animations into sprite sheets, add animations to GameObject

			fin.open(mDataFile);

			if (fin.fail())
			{
				cout << "data retrieval process failed" << endl;
				return;
			}

			// obtains Mario's animation data from the file
			while (!fin.eof())
			{
				getline(fin, line);

				pos = line.find(MARIO_ANIM_SPEED);
				if (pos != string::npos)
				{
					fin >> mAnimationSpeed;
				}

				pos = line.find(NUM_MARIO_ANIM_STATES);
				if (pos != string::npos)
				{
					fin >> mNumAnimStates;
				}

				pos = line.find(MARIO_SPRITE_SIZE);
				if (pos != string::npos)
				{
					fin >> spriteWidth >> spriteHeight;
				}

				pos = line.find(MARIO_IDLE_ANIM);
				if (pos != string::npos)
				{
					for (int i = 0; i < mNumAnimStates; i++)
					{
						fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
						GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

						Animation* anim = new Animation(numSprites, mAnimationSpeed);
						anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
						mAnimationList.push_back(anim);

						mTempList.push_back(pTemp);

						getline(fin, line);
					}
				}

				pos = line.find(MARIO_WALK_ANIM);
				if (pos != string::npos)
				{
					for (int i = 0; i < mNumAnimStates; i++)
					{
						fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
						GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

						Animation* anim = new Animation(numSprites, mAnimationSpeed);
						anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
						mAnimationList.push_back(anim);

						mTempList.push_back(pTemp);

						getline(fin, line);
					}
				}

				pos = line.find(MARIO_JUMP_ANIM);
				if (pos != string::npos)
				{
					for (int i = 0; i < mNumAnimStates; i++)
					{
						fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
						GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

						Animation* anim = new Animation(numSprites, mAnimationSpeed);
						anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
						mAnimationList.push_back(anim);

						mTempList.push_back(pTemp);

						getline(fin, line);
					}
				}
			}

			fin.clear();
			fin.close();
		}

		// creates animations for the Goomba character type
		if (objectType == GOOMBA)
		{
			const string GOOMBA_ANIM_SIZE = "GOOMBA ANIM SPEED";
			const string GOOMBA_SPRITE_SIZE = "GOOMBA SPRITE SIZE";

			const string GOOMBA_WALK_ANIM = "GOOMBA WALK ANIM";

			fin.open(mDataFile);

			if (fin.fail())
			{
				cout << "data retrieval process failed" << endl;
				return;
			}

			// obtains Mario's animation data from the file
			while (!fin.eof())
			{
				getline(fin, line);

				pos = line.find(GOOMBA_ANIM_SIZE);
				if (pos != string::npos)
				{
					fin >> mAnimationSpeed;
				}

				pos = line.find(GOOMBA_SPRITE_SIZE);
				if (pos != string::npos)
				{
					fin >> spriteWidth >> spriteHeight;
				}

				pos = line.find(GOOMBA_WALK_ANIM);
				if (pos != string::npos)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}
			}

			fin.clear();
			fin.close();
		}

		// creates animations for any powerups
		if (objectType >= COIN && objectType <= COIN)
		{
			const string COIN_ANIM_SPEED = "COIN ANIM SPEED";
			const string COIN_SPRITE_SIZE = "COIN SPRITE SIZE";

			const string COIN_NORMAL_ANIM = "COIN NORMAL ANIM";

			fin.open(mDataFile);

			if (fin.fail())
			{
				cout << "data retrieval process failed" << endl;
				return;
			}

			// obtains the powerup's animation data from the file
			while (!fin.eof())
			{
				getline(fin, line);

				pos = line.find(COIN_ANIM_SPEED);
				if (pos != string::npos)
				{
					fin >> mAnimationSpeed;
				}

				pos = line.find(COIN_SPRITE_SIZE);
				if (pos != string::npos)
				{
					fin >> spriteWidth >> spriteHeight;
				}

				pos = line.find(COIN_NORMAL_ANIM);
				if (pos != string::npos)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}
			}

			fin.clear();
			fin.close();
		}

		// draws all interactable background objects
		else if (objectType >= GROUND && objectType <= PIPE_TOP_RIGHT)
		{
			const string GROUND_ANIM = "GROUND BACKGROUND ANIM";
			const string SOLID_BLOCK_ANIM = "SOLID BLOCK BACKGROUND ANIM";
			const string BRICK_ANIM = "BRICK BACKGROUND ANIM";
			const string QUESTION_BLOCK_NORMAL_ANIM = "QUESTION BLOCK NORMAL BACKGROUND ANIM";

			const string FLAG_POLE_ANIM = "FLAG POLE BACKGROUND ANIM";
			const string FLAG_POLE_TOP_ANIM = "FLAG POLE TOP BACKGROUND ANIM";
			const string FLAG_ANIM = "FLAG BACKGROUND ANIM";

			const string PIPE_BODY_LEFT_ANIM = "PIPE BODY LEFT BACKGROUND ANIM";
			const string PIPE_BODY_RIGHT_ANIM = "PIPE BODY RIGHT BACKGROUND ANIM";
			const string PIPE_TOP_LEFT_ANIM = "PIPE TOP LEFT BACKGROUND ANIM";
			const string PIPE_TOP_RIGHT_ANIM = "PIPE TOP RIGHT BACKGROUND ANIM";

			const string BACKGROUND_ANIM_SPEED = "BACKGROUND ANIM SPEED";
			const string BACKGROUND_SPRITE_SIZE = "BACKGROUND SPRITE SIZE";

			fin.open(mDataFile);

			if (fin.fail())
			{
				cout << "data retrieval process failed" << endl;
				return;
			}

			// obtains environmental information from the data file
			while (!fin.eof())
			{
				getline(fin, line);

				pos = line.find(BACKGROUND_ANIM_SPEED);
				if (pos != string::npos)
				{
					fin >> mAnimationSpeed;
				}

				pos = line.find(BACKGROUND_SPRITE_SIZE);
				if (pos != string::npos)
				{
					fin >> spriteWidth >> spriteHeight;
				}

				pos = line.find(GROUND_ANIM);
				if (pos != string::npos && objectType == GROUND)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(SOLID_BLOCK_ANIM);
				if (pos != string::npos && objectType == SOLID_BLOCK)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(BRICK_ANIM);
				if (pos != string::npos && objectType == BRICK)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(QUESTION_BLOCK_NORMAL_ANIM);
				if (pos != string::npos && objectType == QUESTION_MARK_BLOCK)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(FLAG_POLE_ANIM);
				if (pos != string::npos && objectType == FLAG_POLE)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(FLAG_POLE_TOP_ANIM);
				if (pos != string::npos && objectType == FLAG_POLE_TOP)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(FLAG_ANIM);
				if (pos != string::npos && objectType == FLAG)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(PIPE_BODY_LEFT_ANIM);
				if (pos != string::npos && objectType == PIPE_BODY_LEFT)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(PIPE_BODY_RIGHT_ANIM);
				if (pos != string::npos && objectType == PIPE_BODY_RIGHT)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(PIPE_TOP_LEFT_ANIM);
				if (pos != string::npos && objectType == PIPE_TOP_LEFT)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}

				pos = line.find(PIPE_TOP_RIGHT_ANIM);
				if (pos != string::npos && objectType == PIPE_TOP_RIGHT)
				{
					fin >> objectTemp >> numSprites >> sheetWidth >> sheetHeight;
					GraphicsBuffer* pTemp = new GraphicsBuffer(objectTemp, false);

					Animation* anim = new Animation(numSprites, mAnimationSpeed);
					anim->loadSpriteSheet(pTemp, sheetWidth, sheetHeight, spriteWidth, spriteHeight);
					mAnimationList.push_back(anim);

					mTempList.push_back(pTemp);
				}
			}

			fin.clear();
			fin.close();
		}

		// creates animations for enemy types
		else
		{
			// idle / walking animation
			// death animation
		}

		mCurrentFrame = 0;
		mCurrentAnimation = 0;

		mIsInit = true;
	}
}

// cleans up data in the GameObjectAnimator
void GameObjectAnimator::cleanup()
{
	if (!mIsCleanup)
	{
		for (unsigned i = 0; i < mAnimationList.size(); i++)
		{
			delete mAnimationList.at(i);
		}

		mAnimationList.clear();

		for (unsigned i = 0; i < mTempList.size(); i++)
		{
			delete mTempList.at(i);
		}

		mTempList.clear();

		mIsCleanup = false;
	}
}

// adjusts the Unit's state
void GameObjectAnimator::update()
{
	if (mFrameCounter >= mAnimationSpeed)
	{
		if (mCurrentFrame >= mAnimationList.at(mCurrentAnimation)->getNumSprites() - 1)
		{
			mCurrentFrame = 0;
		}

		else
		{
			mCurrentFrame++;
		}

		mFrameCounter = 0;
	}

	else
	{
		mFrameCounter++;
	}

	mAnimationList.at(mCurrentAnimation)->update(mCurrentFrame);
}

// adds an animation to the list
void GameObjectAnimator::addAnimation(Animation* newAnim)
{
	mAnimationList.push_back(newAnim);
}

// switches to a new animation
void GameObjectAnimator::setAnimation(int animNumber)
{
	if (mAnimationList.at(mCurrentAnimation)->getNumSprites() > mAnimationList.at(animNumber)->getNumSprites())
	{
		mCurrentFrame = 0;
	}

	mCurrentAnimation = animNumber;
}

// gets the value of mCurrentAnimation
int GameObjectAnimator::getCurrentAnimation()
{
	return mCurrentAnimation;
}

// gets the current animation frame
int GameObjectAnimator::getCurrentFrame()
{
	return mCurrentFrame;
}

// gets the Unit's currently playing Animation
Animation* GameObjectAnimator::getAnimation()
{
	return mAnimationList.at(mCurrentAnimation);
}