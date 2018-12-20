#pragma once

#include <MemoryTracker.h>
#include <PerformanceTracker.h>

#include <map>
#include <string>

class GraphicsSystem;
class GraphicsBuffer;

typedef std::string GraphicsBufferKey;

class GraphicsBufferManager : public Trackable
{
public:
	// constructor and destructor
	GraphicsBufferManager();
	~GraphicsBufferManager();

	// add a GraphicsBuffer to or delete a GraphicsBuffer from the map
	void addGraphicsBuffer(const GraphicsBufferKey& key, std::string fileName);
	void deleteGraphicsBuffer(const GraphicsBufferKey& key);

	// remove and delete all GraphicsBuffers from the map
	void clear();

	// accessors
	GraphicsBuffer* getGraphicsBuffer(const GraphicsBufferKey& key);

private:
	std::map<GraphicsBufferKey, GraphicsBuffer*> mGraphicsBufferMap;	// "map" of GraphicsBuffers

	bool mIsDestroyed;													// checks if the GrpahicsBufferManager object is destroyed or not
};