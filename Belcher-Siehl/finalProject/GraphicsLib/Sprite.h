#pragma once

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

class GraphicsBuffer;

// the Sprite class
class Sprite : public Trackable
{
public:
	// constructor
	Sprite(GraphicsBuffer* pGraphic, float sourceLocX, float sourceLocY, int width, int height);
	Sprite(GraphicsBuffer* pGraphic, float sourceLocX, float sourceLocY);
	Sprite();

	// destructor
	~Sprite();

	// accessors
	float getLocX();
	float getLocY();
	int getWidth();
	int getHeight();
	GraphicsBuffer* getGraphic();

private:
	GraphicsBuffer* mpGraphic;
	float mSourceLocX;
	float mSourceLocY;
	int mWidth;
	int mHeight;
};