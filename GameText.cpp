#include "GameText.h"

GameText::GameText(LoaderParams* pParams)
{
	//make a set rect method so I do not see three of the same thing, inside this file

	game_text_rect = new SDL_Rect;
	game_text_rect->x = pParams->GetX();
	game_text_rect->y = pParams->GetY();
	game_text_rect->w = pParams->GetWidth();
	game_text_rect->h = pParams->GetHeight();
	game_text_id = pParams->GetTextureID();

	
}

GameText::GameText(LoaderParams* pParams, unsigned int passed_text_size)
{
	game_text_collider = new CCollisionRectangle;

	game_text_rect = new SDL_Rect;
	game_text_rect->x = pParams->GetX();
	game_text_rect->y = pParams->GetY();
	game_text_rect->w = pParams->GetWidth();
	game_text_rect->h = pParams->GetHeight();
	game_text_id = pParams->GetTextureID();

	game_text_size = passed_text_size;

	game_text_collider->SetCollisionRect(game_text_rect->x, game_text_rect->y, game_text_rect->w, game_text_rect->h);
}

GameText::GameText(LoaderParams* pParams, std::string passed_message, unsigned int passed_text_size)
{
	game_text_rect = new SDL_Rect;
	game_text_rect->x = pParams->GetX();
	game_text_rect->y = pParams->GetY();
	game_text_rect->w = pParams->GetWidth();
	game_text_rect->h = pParams->GetHeight();
	game_text_id = pParams->GetTextureID();

	game_text_size = passed_text_size;

	SetGameTextMessage(passed_message);
}


GameText::~GameText()
{

	delete game_text_rect;
}

void GameText::AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{
	SDL_SetTextureColorMod(game_text_texture, passed_r_value, passed_g_value, passed_b_value);

	game_text_message_highlighted = true;
}

void GameText::SetOriginalColors()
{
		
    Uint8* temp_r = new Uint8;
	Uint8* temp_g = new Uint8;
	Uint8* temp_b = new Uint8;

	if (SDL_GetTextureColorMod(game_text_texture, temp_r, temp_g, temp_b))
	{
		game_text_original_color.SetColorValues(*temp_r, *temp_g, *temp_b);

		std::cout << "colors r - "<< *temp_r << ", g - " << *temp_g << ", b - " << *temp_b  << std::endl;

		game_text_message_highlighted = false;
	}
	else 
	{
		//if failed set original colors

		game_text_original_color.SetColorValues(250, 250, 250);

		game_text_message_highlighted = false;
	}

	delete temp_r;
	delete temp_g;
	delete temp_b;

}

void GameText::ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{
	if (game_text_message_highlighted == false)
	{
		AlterTextureColor(passed_r_value, passed_g_value, passed_b_value);

		game_text_message_highlighted = true;
	}
	else
	{
		RevertAlteredTextureColor();

		game_text_message_highlighted = false;
	}

}

Color GameText::GetOringinalColors()
{
	return game_text_original_color;
}

void GameText::RevertAlteredTextureColor()
{
	
	//SDL_SetTextureColorMod(game_text_texture, game_text_original_color.GetColorValueR(), game_text_original_color.GetColorValueG(), game_text_original_color.GetColorValueB());
	SDL_SetTextureColorMod(game_text_texture, 255,255,255);
		
	game_text_message_highlighted = false;
}

//load
bool GameText::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{
	TTF_Font* font = TTF_OpenFont("resources/fonts/PressStart2P.ttf", game_text_size);
	//if font NULL
	SDL_Color color = { 255,255,255 };

	if (game_text_id.empty())
	{
		game_text_id = "Start Game";
		SetGameTextMessage(game_text_id);
	}
	else if (game_text_message != NULL) 
	{

	}
	else
	{
		SetGameTextMessage(game_text_id);
	}

	

	SDL_Surface* textSurface = NULL;

	textSurface = TTF_RenderText_Solid(font, game_text_message, color);

	if (textSurface == NULL)
	{
		if (Developer::GetInstance()->is_debug_mode())
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
		if (Developer::GetInstance()->is_debug_mode())
		{
			printf("GameText::LoadGameObjectContent() failed to open font error %s\n", SDL_GetError());
		}
		return false;
	}

	//Get Original texture Colors
	SetOriginalColors();
	


	if (Developer::GetInstance()->is_debug_mode())
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
		
	if (Developer::GetInstance()->is_debug_mode())
	{
		std::cout << "Message from " << passed_message <<  " to " << game_text_message << std::endl;
	}

	
}
void GameText::SetGameTextMessage(char* passed_message)
{

	game_text_message = passed_message;
}


bool GameText::CheckForSingleCollision(CCollisionRectangle* passed_CollisionRectangle)
{
	//Get rect of this GameText

	SDL_Rect alpha = *game_text_collider->GetCollisionRect();

	SDL_Rect beta = *passed_CollisionRectangle->GetCollisionRect();


	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = alpha.x;
	rightA = alpha.x + alpha.w;
	topA = alpha.y;
	bottomA = alpha.y + alpha.h;

	//Calculate the sides of rect B
	leftB = beta.x;
	rightB = beta.x + beta.w;
	topB = beta.y;
	bottomB = beta.y + beta.h;

	//If any of the sides from A are outside of B

	if (bottomA <= topB)
	{
		return false;
	}
	//same comparison
	if (topA >= bottomB)
	{
		return false;
	}


	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true; 
}