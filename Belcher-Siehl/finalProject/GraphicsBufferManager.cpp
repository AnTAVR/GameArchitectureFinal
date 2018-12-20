#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

// constructor for the GraphicsBufferManager class
GraphicsBufferManager::GraphicsBufferManager()
{
	mIsDestroyed = false;
}

// destructor for the GraphicsBufferManager class
GraphicsBufferManager::~GraphicsBufferManager()
{
	if (!mIsDestroyed)
	{
		clear();
		mIsDestroyed = true;
	}
}

// adds a GraphicsBuffer to the map
void GraphicsBufferManager::addGraphicsBuffer(const GraphicsBufferKey& key, string fileName)
{
	GraphicsBuffer* pGraphicsBuffer = NULL;

	// figure out if it exists already
	map<GraphicsBufferKey, GraphicsBuffer*>::iterator iter = mGraphicsBufferMap.find(key);

	// check if the GraphicsBuffer is already in the map
	if (iter == mGraphicsBufferMap.end())
	{
		// if it is not already there, create and add it
		pGraphicsBuffer = new GraphicsBuffer(fileName, true);
		mGraphicsBufferMap[key] = pGraphicsBuffer;
	}
}

// removes and deletes a GraphicsBuffer from the map (GraphicsBufferKey)
void GraphicsBufferManager::deleteGraphicsBuffer(const GraphicsBufferKey& key)
{
	// tests if the GraphicsBuffer already exists
	map<GraphicsBufferKey, GraphicsBuffer*>::iterator iter = mGraphicsBufferMap.find(key);

	// if the GraphicsBuffer is found, delete and remove it
	if (iter != mGraphicsBufferMap.end())
	{
		delete iter->second;
		mGraphicsBufferMap.erase(iter);
	}
}

// clears all the GraphicsBuffers from the map
void GraphicsBufferManager::clear()
{
	map<GraphicsBufferKey, GraphicsBuffer*>::iterator iter;

	while (mGraphicsBufferMap.size() > 0)
	{
		deleteGraphicsBuffer(mGraphicsBufferMap.begin()->first);
	}
}

// gets a chosen GraphicsBuffer from the map
GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(const GraphicsBufferKey& key)
{
	map<GraphicsBufferKey, GraphicsBuffer*>::const_iterator iter = mGraphicsBufferMap.find(key);

	if (iter != mGraphicsBufferMap.end())
	{
		return iter->second;
	}

	else
	{
		return NULL;
	}
}