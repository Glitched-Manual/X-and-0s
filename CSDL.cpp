#include "CSDL.h"



CSDL::CSDL(unsigned int passed_screen_width, unsigned int passed_screen_height)
{
	SCREEN_WIDTH  = passed_screen_width;

	SCREEN_HEIGHT = passed_screen_height;

	LoadInputMap();
}

bool CSDL::Init()
{
	//audio not working
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{

		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");

			return false;
		}

		//Create window

		if (!this->createSDLWindow(SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			return false;
		}
		else
		{
			//initialize event

			sdl2_Game_Event = new SDL_Event();

			// create renderer
			if (!this->createSDLRenderer())
			{
				return false;
			}
			else
			{

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return false;
				}

				if (SDL_WasInit(SDL_INIT_AUDIO) != 0)
				{
					if (debug.is_debug_mode())
					{
						printf("Audio has been initialized.\n");
					}
					   //Initialize SDL_mixer - uncomment return later
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						if (debug.is_debug_mode()) 
						{
							printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
						}

						
					  //	return false;
					}
				}
				else 
				{
					if (debug.is_debug_mode())
					{
						printf("Audio was not initialized! SDL_mixer Error: %s\n", Mix_GetError());
					}
					

					return false;
				}				
				
				
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					if (debug.is_debug_mode())
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					}
				

					return false;
				}

				//Check for a GameController

				if (SDL_NumJoysticks() < 1)
				{
					if (debug.is_debug_mode())
					{
						printf("Warning: No joysticks connected! error %s\n", SDL_GetError());
					}
					
				}
				else
				{

					for (int i = 0; i < SDL_NumJoysticks(); ++i)
					{
						//if index found is a controller open it
						if (SDL_IsGameController(i))
						{
							sdl2_GameController = SDL_GameControllerOpen(i);
							if (sdl2_GameController)
							{
								if (debug.is_debug_mode())
								{
									char* gameControllerMapping;
									std::cout << "The controller was reconized" << std::endl;
									gameControllerMapping = SDL_GameControllerMapping(sdl2_GameController);
									std::cout << "Controller mapping is " << gameControllerMapping << std::endl;
									
								}
																
								break;
							}
							else
							{
								if (debug.is_debug_mode())
								{
									fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
								}
								
							}
						}
					}

				}
			}
		}
	}
	return true;
}

bool CSDL::createSDLWindow(unsigned int passed_SCREEN_WIDTH, unsigned int passed_SCREEN_HEIGHT)
{

	sdl2_GameWindow = NULL;
	sdl2_GameWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, passed_SCREEN_WIDTH, passed_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (sdl2_GameWindow == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("CSDL::createSDLWindow error: SDL2_Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
				
		return false;
	}


	return true;
}

bool CSDL::createSDLRenderer()
{
	sdl2_GameRenderer = SDL_CreateRenderer(sdl2_GameWindow, -1, SDL_RENDERER_ACCELERATED);

	if (sdl2_GameRenderer == NULL)
	{
		if(debug.is_debug_mode()) 
		{
			printf("CSDL::createSDLRenderer() error: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
				
		return false;
	}

	return true;
}

void CSDL::LoadInputMap()
{
	sdl2_Input_Map["UP"] = UP;
	sdl2_Input_Map["DOWN"] = DOWN;
	sdl2_Input_Map["LEFT"] = LEFT;
	sdl2_Input_Map["RIGHT"] = RIGHT;
	sdl2_Input_Map["START"] = START;
	sdl2_Input_Map["SELECT"] = SELECT;
	sdl2_Input_Map["A_ACTION"] = A_ACTION;
	sdl2_Input_Map["B_ACTION"] = B_ACTION;
	sdl2_Input_Map["ESCAPE"] = ESCAPE;
	sdl2_Input_Map["SPACE"] = SPACE;
	
}

/*

  Keyboard and controller input  to action check

*/



bool CSDL::ButtonInputCheck(std::string input_to_check)
{
	switch (sdl2_Input_Map[input_to_check])
	{
	case UP:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) return true;

		else if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) return true;

		else if ( (sdl2_Game_Event->key.keysym.sym == SDLK_UP) && (sdl2_Game_Event->type == SDL_KEYDOWN) ) return true;

		else return false;

		break;

	case DOWN:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_DOWN ) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	case LEFT:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_LEFT ) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	case RIGHT:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT ) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_RIGHT) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;
	case START:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_START ) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_RETURN ) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	case SELECT:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE ) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_TAB) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	case A_ACTION:

		if (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_A ) return true;

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_a ) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	case B_ACTION:

		/* sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_B is true when any keyboard key pressed

		   any keyboard key sdl2_Game_Event->cbutton.button == 1
		    SDL_CONTROLLER_BUTTON_B == 1

			sdl2_Game_Event->cbutton.button == SDL_CONTROLLERBUTTONDOWN used
		*/
		if ( (sdl2_Game_Event->cbutton.button == SDL_CONTROLLER_BUTTON_B) && (sdl2_Game_Event->cbutton.state == SDL_PRESSED))
		{
			if (debug.is_debug_mode())
			{
				std::cout << "B pressed" << std::endl;
			}

			return true;

		}
				

		else if ((sdl2_Game_Event->key.keysym.sym == SDLK_s) && (sdl2_Game_Event->type == SDL_KEYDOWN))
		{
			if (debug.is_debug_mode())
			{
				std::cout << "S pressed" << std::endl;
			}

			return true;
		}

		else return false;

		break;

	case ESCAPE:
		//keyboard only
		if ((sdl2_Game_Event->key.keysym.sym == SDLK_ESCAPE) && (sdl2_Game_Event->type == SDL_KEYDOWN))
		{
			if (debug.is_debug_mode())
			{
				std::cout << "ESCAPE pressed" << std::endl;
			}

			return true;
		}

		else return false;

		break;

	case SPACE:
		//keyboard only
		if ((sdl2_Game_Event->key.keysym.sym == SDLK_SPACE) && (sdl2_Game_Event->type == SDL_KEYDOWN)) return true;

		else return false;

		break;

	default:

		return false;
		break;
	}


}
