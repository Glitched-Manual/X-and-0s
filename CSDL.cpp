#include "CSDL.h"



CSDL::CSDL(unsigned int passed_screen_width, unsigned int passed_screen_height)
{
	SCREEN_WIDTH  = passed_screen_width;

	SCREEN_HEIGHT = passed_screen_height;
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
	sdl2_GameWindow = SDL_CreateWindow("Launch Pad", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, passed_SCREEN_WIDTH, passed_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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