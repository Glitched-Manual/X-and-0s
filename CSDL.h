#include "cross_sdl.h"


#include <iostream>
#include <cstdio>

#pragma once
class CSDL
{
	SDL_Window* sdl2_GameWindow;
	SDL_Renderer* sdl2_GameRenderer;
	SDL_Event* sdl2_Game_Event;
	SDL_GameController* sdl2_GameController;

public:
	CSDL();
	bool Init();
	bool createSDLWindow(unsigned int SCREEN_WIDTH, unsigned int SCREEN_HEIGHT);
	bool createSDLRenderer();

	 SDL_Window* GetSDLWindow() { return sdl2_GameWindow; }
    SDL_Renderer* GetSDLRenderer()  { return sdl2_GameRenderer; }
	 SDL_Event* GetSDLGameEvent() { return sdl2_Game_Event;  }
	SDL_GameController* GetGameController() { return sdl2_GameController; }
};

