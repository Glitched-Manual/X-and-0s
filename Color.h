#include <iostream>
#include "cross_sdl.h"

#ifndef COLOR_H
#define COLOR_H

struct Color
{
	Color();
	Color(Uint8 passed_r, Uint8 passed_g, Uint8 passed_b );

	Uint8 GetColorValueR() { return r; }

	Uint8 GetColorValueG() { return g; }

	Uint8 GetColorValueB() { return b; }

private:
	//records red value 0-250
	Uint8 r;

	//records green value 0-250
	Uint8 g;

	//records blue value 0-250
	Uint8 b;

};



#endif // COLOR_H