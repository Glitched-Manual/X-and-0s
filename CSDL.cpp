#include "CSDL.h"



CSDL::CSDL()
{

}

bool CSDL::Init()
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

		if (!this->createSDLWindow(960, 720))
		{
			return false;
		}
		else
		{
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


				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					return false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}

			}
		}
	}
	return true;
}

bool CSDL::createSDLWindow(unsigned int passed_SCREEN_WIDTH, unsigned int passed_SCREEN_HEIGHT)
{

	primeSDLGameWindow = NULL;
	primeSDLGameWindow = SDL_CreateWindow("Launch Pad", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, passed_SCREEN_WIDTH, passed_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (getSDLWindow() == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}


	return true;
}

bool CSDL::createSDLRenderer()
{

	return true;
}