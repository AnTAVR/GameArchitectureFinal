#include "Color.h"
#include <cstdint>

// default constructor for the Color class
Color::Color()
{
	mColor = { 0, 0, 0 };
}

// constructor for the Color class
Color::Color(int r, int g, int b)
{
	mColor = { (Uint8)r, (Uint8)g, (Uint8)b };
}

// destructor for the Color class
Color::~Color()
{
	
}