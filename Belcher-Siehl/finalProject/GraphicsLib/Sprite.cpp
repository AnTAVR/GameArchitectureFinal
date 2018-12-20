#include "Sprite.h"
#include "GraphicsBuffer.h"

// constructor for the Sprite class
Sprite::Sprite(GraphicsBuffer* pGraphic, float sourceLocX, float sourceLocY, int width, int height)
{
	mpGraphic = pGraphic;
	mSourceLocX = sourceLocX;
	mSourceLocY = sourceLocY;
	mWidth = width;
	mHeight = height;
};

// constructor for the Sprite class (no specified width or height)
Sprite::Sprite(GraphicsBuffer* pGraphic, float sourceLocX, float sourceLocY)
{
	mpGraphic = pGraphic;
	mSourceLocX = sourceLocX;
	mSourceLocY = sourceLocY;

	mWidth = pGraphic->getWidth();
	mHeight = pGraphic->getHeight();
}

// default constructor for the Sprite class
Sprite::Sprite()
{
	mpGraphic = NULL;
	mSourceLocX = 0;
	mSourceLocY = 0;
	mWidth = 0;
	mHeight = 0;
};

// destructor for the Sprite class
Sprite::~Sprite()
{
	
}

// accessor for mSourceLocX
float Sprite::getLocX() 
{ 
	return mSourceLocX; 
}

// accessor for mSourceLocY
float Sprite:: getLocY()
{
	return mSourceLocY;
}

// accessor for mWidth
int Sprite::getWidth()
{
	return mWidth;
}

// accessor for mHeight
int Sprite::getHeight()
{
	return mHeight;
}

// accessor for mGraphic
GraphicsBuffer* Sprite::getGraphic()
{
	return mpGraphic;
}