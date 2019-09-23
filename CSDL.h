#include "cross_sdl.h"
#include "Developer.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <map>

#ifndef CSDL_H
#define CSDL_H


struct Developer;
class CSDL
{
	SDL_Window* sdl2_GameWindow;
	SDL_Renderer* sdl2_GameRenderer;
	SDL_Event* sdl2_Game_Event;
	SDL_GameController* sdl2_GameController;
	
	enum ButtonValue { UP, DOWN, LEFT, RIGHT, START, SELECT, A_ACTION, B_ACTION, ESCAPE, SPACE, ENTER, LEFT_CLICK,RIGHT_CLICK};
	// add ENTER
	std::map<std::string, ButtonValue> sdl2_Input_Map;

	unsigned int SCREEN_WIDTH;
		
	unsigned int SCREEN_HEIGHT;
public:
	CSDL(unsigned int passed_screen_width, unsigned int passed_screen_height);
	bool Init();
	bool createSDLWindow(unsigned int SCREEN_WIDTH, unsigned int SCREEN_HEIGHT);
	bool createSDLRenderer();

	/*
	for setting common player button input. Such as:

	Mouse Clicks

	Keyboard Arrow Keys

	Controller Buttons

	My developer input proceded this.
	
	*/
	void LoadInputMap();

	 SDL_Window* GetSDLWindow() { return sdl2_GameWindow; }
    SDL_Renderer* GetSDLRenderer()  { return sdl2_GameRenderer; }
	 SDL_Event* GetSDLGameEvent() { return sdl2_Game_Event;  }
	SDL_GameController* GetGameController() { return sdl2_GameController; }

	// Button interperter

	bool ButtonInputCheck(std::string input_to_check);

	bool ButtonPressedCheck();

	bool ButtonReleasedCheck();

	//to solve button when arrow keys held issue
	bool ArrowKeyInput();
};

#endif //CSDL_H