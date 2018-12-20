#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include <stdlib.h>

#include <iostream>

using namespace std;

// constructor for the GraphicsSystem class
GraphicsSystem::GraphicsSystem()
{
	mIsInit = false;

	mpWindow = NULL;
	mpRenderer = NULL;
}

// destructor for the GraphicsSystem class
GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

// initializes the Allegro / sound library files
int GraphicsSystem::init(int width, int height)
{
	if (!mIsInit)
	{
		mWidth = width;
		mHeight = height;

		mpWindow = SDL_CreateWindow("Super_Mario_Bros.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, 0);
		mpRenderer = SDL_CreateRenderer(mpWindow, -1, 0);
		mpBackbuffer = new GraphicsBuffer(SDL_GetWindowSurface(mpWindow), true);
		mIsInit = true;
	}

	return 0;
}

// cleans up and destroys all existing files
void GraphicsSystem::cleanup()
{
	if (mIsInit)
	{
		delete mpBackbuffer;
		SDL_DestroyWindow(mpWindow);
		mIsInit = false;
	}
}

// accessor for mDisplay's width
int GraphicsSystem::getWidth()
{
	return mWidth;
}

// accessor for mDisplay's height
int GraphicsSystem::getHeight()
{
	return mHeight;
}

// accessor for mBackbuffer
GraphicsBuffer* GraphicsSystem::getBuffer()
{
	return mpBackbuffer;
}

// flips the display
void GraphicsSystem::flip()
{
	SDL_RenderPresent(mpRenderer);
}

// draws a sprite
void GraphicsSystem::draw(float locX, float locY, Sprite* sprite, float scale, bool isRightFacing)
{
	GraphicsBuffer* pSpriteBuffer = sprite->getGraphic();
	
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer, pSpriteBuffer->mpSurface);

	SDL_Rect spriteRect;
	spriteRect.x = (int)sprite->getLocX();
	spriteRect.y = (int)sprite->getLocY();
	spriteRect.w = (int)sprite->getWidth();
	spriteRect.h = (int)sprite->getHeight();

	SDL_Rect rendererRect;
	rendererRect.x = (int)locX;
	rendererRect.y = (int)locY;
	rendererRect.w = (int)(sprite->getWidth() * scale);
	rendererRect.h = (int)(sprite->getHeight() * scale);

	if (isRightFacing)
	{
		SDL_RenderCopy(mpRenderer, pTexture, &spriteRect, &rendererRect);
	}

	else
	{
		SDL_RenderCopyEx(mpRenderer, pTexture, &spriteRect, &rendererRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	SDL_DestroyTexture(pTexture);
}

// draws a sprite to a specific GraphicsBuffer {DOES NOT CURRENTLY WORK}
void GraphicsSystem::draw(GraphicsBuffer* pTarget, float locX, float locY, Sprite* sprite, float scale, bool isRightFacing)
{
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer, mpBackbuffer->mpSurface);

	SDL_Rect spriteRect;
	spriteRect.x = (int)sprite->getLocX();
	spriteRect.y = (int)sprite->getLocY();
	spriteRect.w = (int)sprite->getWidth();
	spriteRect.h = (int)sprite->getHeight();

	SDL_Rect rendererRect;
	rendererRect.x = (int)locX;
	rendererRect.y = (int)locY;
	rendererRect.w = (int)(sprite->getWidth() * scale);
	rendererRect.h = (int)(sprite->getHeight() * scale);

	if (isRightFacing)
	{
		SDL_RenderCopy(mpRenderer, pTexture, &spriteRect, &rendererRect);
	}

	else
	{
		SDL_RenderCopyEx(mpRenderer, pTexture, &spriteRect, &rendererRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	SDL_DestroyTexture(pTexture);
}

// writes text
void GraphicsSystem::writeText(float locX, float locY, Font* font, Color &color, string text)
{
	SDL_Surface* pTextSurface = TTF_RenderText_Solid(font->mpFont, (text).c_str(), color.mColor);
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer, pTextSurface);

	SDL_Rect textRect;
	textRect.x = (int)locX;
	textRect.y = (int)locY;
	textRect.w = (int)(strlen((text).c_str()) * font->getSize());
	textRect.h = font->getSize();

	SDL_RenderCopy(mpRenderer, pTexture, NULL, &textRect);

	SDL_FreeSurface(pTextSurface);
	SDL_DestroyTexture(pTexture);
}

// writes text on a specific GraphicsBuffer
void GraphicsSystem::writeText(GraphicsBuffer* pTarget, float locX, float locY, Font &font, Color &color, string text)
{
	pTarget->mpSurface = TTF_RenderText_Solid(font.mpFont, (text).c_str(), color.mColor);
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer, pTarget->mpSurface);

	SDL_Rect textRect;
	textRect.x = (int)locX;
	textRect.y = (int)locY;
	textRect.w = pTarget->getWidth();
	textRect.h = pTarget->getHeight();

	SDL_RenderCopy(mpRenderer, pTexture, NULL, &textRect);
	SDL_DestroyTexture(pTexture);
}

// saves a specific GraphicsBuffer
void GraphicsSystem::saveBuffer(GraphicsBuffer* pTarget, string filename)
{
	if (!SDL_SaveBMP(pTarget->mpSurface, (filename).c_str()))
	{
		cout << "failed to save buffer" << endl;
	}
}