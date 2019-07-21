#include "cross_sdl.h"


#include <iostream>
#include <cstdio>

#pragma once
class CSDL
{
	SDL_Window* primeSDLGameWindow;
	SDL_Renderer* primeSDLGameRenderer;

public:
	CSDL();
	bool Init();
	bool createSDLWindow(unsigned int SCREEN_WIDTH, unsigned int SCREEN_HEIGHT);
	bool createSDLRenderer();

	const SDL_Window* getSDLWindow() { return primeSDLGameWindow; }
	const SDL_Renderer* getSDLRenderer() { return primeSDLGameRenderer; }
};

