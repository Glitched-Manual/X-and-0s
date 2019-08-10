#include "GameText.h"

GameText::GameText(LoaderParams* pParams)
{
	game_text_rect = new SDL_Rect;
	game_text_rect->x = pParams->GetX();
	game_text_rect->y = pParams->GetY();
	game_text_rect->w = pParams->GetWidth();
	game_text_rect->h = pParams->GetHeight();
	game_text_id = pParams->GetTextureID();

	
}

//load
bool GameText::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{
	TTF_Font* font = TTF_OpenFont("PressStart2P.ttf", 60);
	SDL_Color color = { 255,255,255 };

	if (game_text_id.empty())
	{
		game_text_id = "Start Game";
	}

	SetGameTextMessage(game_text_id);

	SDL_Surface* textSurface = NULL;

	textSurface = TTF_RenderText_Solid(font, game_text_message, color);

	if (textSurface == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("GameText::LoadGameObjectContent failed to create surface error: %s\n", SDL_GetError());
		}
		return false;
	}

	//SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello Manual", color);
	game_text_box_width = textSurface->w;
    game_text_box_height = textSurface->h;

	game_text_rect->w = game_text_box_width;
	game_text_rect->h = game_text_box_height;
	//game_text_rect->x center x pos on screen
	game_text_rect->x = game_text_rect->x - (game_text_box_width / 2);


	game_text_texture = NULL;

	game_text_texture = SDL_CreateTextureFromSurface(passed_Renderer, textSurface);
	if (game_text_texture == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("GameText::LoadGameObjectContent() failed to open font error %s\n", SDL_GetError());
		}
	}

	if (debug.is_debug_mode())
	{
		std::cout << "Finished loading Game text object " << game_text_id << std::endl;
	}
	game_text_content_loaded = true;
	return true;

}
//render
void  GameText::Draw(SDL_Renderer* passed_Renderer)
{		
	SDL_RenderCopyEx(passed_Renderer, game_text_texture, NULL, game_text_rect, 0.0, NULL, SDL_FLIP_NONE);
}
//update? change text?
void GameText::Update()
{

}
//clean
void GameText::CleanGameObjectContent()
{

}
bool GameText::GetContentLoadedStatus()
{
	return game_text_content_loaded;
}

void GameText::SetGameTextMessage( std::string passed_message)
{
	set_text_used = true;
	 game_text_message = new char[passed_message.length() + 1];
	strcpy(game_text_message, passed_message.c_str());
		
	if (debug.is_debug_mode())
	{
		std::cout << "Message from " << passed_message <<  " to " << game_text_message << std::endl;
	}

	
}

GameText::~GameText()
{
	

}