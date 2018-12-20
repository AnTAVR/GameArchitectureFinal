#pragma once

#include <string>
#include <map>
#include <Trackable.h>

//using namespace std;

class Widget;

typedef std::string WidgetKey;

class WidgetManager : public Trackable
{
public:
	WidgetManager(){};
	~WidgetManager();

	void cleanup();

	Widget* createAndManageWidget( const WidgetKey& key, float contents ); 
	void deleteWidget( const WidgetKey& key );
	void deleteWidget( Widget* pWidget );

	Widget* getWidget( const WidgetKey& key ) const;

private:
	std::map<WidgetKey, Widget*> mMap;

};
