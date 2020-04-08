#pragma once
#include "SDL/SDL_stdinc.h"

class Wall
{
	// F
	struct Color
	{
		Uint8 red	= 255;
		Uint8 green	= 255;
		Uint8 blue	= 255;
		Uint8 alpha	= 255;
	};

public:
	Wall();
	~Wall();

private:
	// F
	Color mColor;
	// Œú‚³
	unsigned int mThickness;
};

