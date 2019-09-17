#include "PromptWindow.h"


PromptWindow::PromptWindow(LoaderParams* pParams, CSDL* passed_csdl_obj)
{
	SDL_Rect* prompt_background_texture_rect = new SDL_Rect;
	prompt_window_id = pParams->GetTextureID();

	prompt_background_texture_rect->x = pParams->GetX();
	prompt_background_texture_rect->y = pParams->GetY();
	prompt_background_texture_rect->w = pParams->GetWidth();
	prompt_background_texture_rect->h = pParams->GetHeight();


	prompt_background_texture_rect->x = prompt_background_texture_rect->x - (prompt_background_texture_rect->w / 2);
	prompt_background_texture_rect->y = prompt_background_texture_rect->y - (prompt_background_texture_rect->h / 2);

	prompt_texture_rect_map[prompt_window_id] = prompt_background_texture_rect;


}

PromptWindow::~PromptWindow()
{

}

bool PromptWindow::LoadGameObjectContent(SDL_Renderer* passed_renderer)
{
	CreateBackGroundTexture(passed_renderer);
	prompt_window_content_loaded = true;
	if(Developer::GetInstance()->is_debug_mode()) 
	{
		std::cout << "PromptWindow::LoadGameObjectContent  was loaded" << std::endl;
	}

	if (!game_texts_vector.empty())
	{
		
		for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
		{
			
			(*game_text_object_index)->LoadGameObjectContent(passed_renderer);

		}
	}


	return true;
}
void PromptWindow::Draw(SDL_Renderer* passed_Renderer)
{
	 //draw bottom to top	
	SDL_RenderCopyEx(passed_Renderer, prompt_texture_map[prompt_window_id], NULL, prompt_texture_rect_map[prompt_window_id], 0.0, NULL, SDL_FLIP_NONE);

	// Text Play Again?
    
	//Text YES

	//Text NO
	if (!game_texts_vector.empty())
	{


		for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
		{


			(*game_text_object_index)->Draw(passed_Renderer);


		}
	}
	/*if (Developer::GetInstance()->is_debug_mode())
	{
		std::cout << "Promt "<< prompt_window_id <<" was drawn!" << std::endl;
	}

	*/
}
void PromptWindow::Update()
{
	
}
void PromptWindow::CleanGameObjectContent()
{

}




void PromptWindow::ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void PromptWindow::AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void PromptWindow::AlterTextureColor(std::string passed_string, Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{
	/*
	if (!game_texts_vector.empty())
	{


		for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
		{
			if ((*game_text_object_index)->GetGameObjectID == passed_string)
			{

				(*game_text_object_index)->AlterTextureColor(passed_r_value, passed_g_value, passed_b_value);
			}

		}
	}
	*/

	
	/*

	//never works
	std::map<std::string, GameText*>::iterator finder;
	finder = game_texts_map.find(passed_string);

	if (finder != game_texts_map.end())
	{
		game_texts_map[passed_string]->AlterTextureColor(passed_r_value, passed_g_value, passed_b_value);
	}

	else
	{
		if (Developer::GetInstance()->is_debug_mode())
		{
			std::cout << "map key not found" << std::endl;
		}
		
	}
	*/

	if (!game_texts_vector.empty())
	{


		for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
		{
			if ((*game_text_object_index)->GetGameObjectID() == passed_string)
			{
				(*game_text_object_index)->AlterTextureColor(passed_r_value, passed_g_value, passed_b_value);
				std::cout << "map key found in vector" << std::endl;
			}

		}
	}
}

void PromptWindow::RevertAlteredTextureColor()
{

}

void PromptWindow::RevertAlteredTextureColor(std::string passed_string)
{

	/*
	if (!game_texts_vector.empty())
	{
		
		for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
		{
			if ((*game_text_object_index)->GetGameObjectID == passed_string)
			{

				(*game_text_object_index)->RevertAlteredTextureColor();
			}

		}
	}

	*/

	std::map<std::string, GameText*>::iterator finder;
	finder = game_texts_map.find(passed_string);

	if (finder != game_texts_map.end())
	{
		 game_texts_map[passed_string]->RevertAlteredTextureColor();
	}

	else
	{
		if (Developer::GetInstance()->is_debug_mode())
		{
			std::cout << "map key not found" << std::endl;
		}

		if (!game_texts_vector.empty())
		{
			
			for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
			{
				if ((*game_text_object_index)->GetGameObjectID() == passed_string)
				{
					(*game_text_object_index)->RevertAlteredTextureColor();
					std::cout << "map key found in vector" << std::endl;
				}

			}
		}

	}
}

bool PromptWindow::GetAreColorsAltered(std::string passed_string)
{
	std::map<std::string, GameText*>::iterator finder;
	finder = game_texts_map.find(passed_string);

	if ( finder != game_texts_map.end() )
	{
		return game_texts_map[passed_string]->GetAreColorsAltered();
	}

	if (Developer::GetInstance()->is_debug_mode())
	{
		std::cout << "map key not found" << std::endl;
		if (!game_texts_vector.empty())
		{

			for (std::vector<GameText*>::iterator game_text_object_index = game_texts_vector.begin(); game_text_object_index != game_texts_vector.end(); game_text_object_index++)
			{
				if ((*game_text_object_index)->GetGameObjectID() == passed_string)
				{
					
					std::cout << "map key found in vector" << std::endl;
					return (*game_text_object_index)->GetAreColorsAltered();
				}

			}
		}
	}

	return false;
}

void PromptWindow::SetOriginalColors()
{

}


void PromptWindow::AlterTextureAlpha(Uint8 alpha_value, std::string passed_texture_key)
{

}

/*


*/


bool PromptWindow::CreateBackGroundTexture(SDL_Renderer* passed_renderer)
{
	//create SDL_Surface and texture

	SDL_Surface* propmt_background_surface = NULL;
	SDL_Texture* prompt_background_texture = NULL;

	/*
	
	SDL_Surface* SDL_CreateRGBSurface(Uint32 flags,
                                  int    width,
                                  int    height,
                                  int    depth,
                                  Uint32 Rmask,
                                  Uint32 Gmask,
                                  Uint32 Bmask,
                                  Uint32 Amask);

      Lol how do I learn color masks?

	  I think I got it.

	  Color mask data is stored in the most significant byte. #1 most significant #4 least significant
	     
       mask =  0x#1#2#3#4; position of value
	   rmask = 0xff000000;

	*/
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	propmt_background_surface = SDL_CreateRGBSurface(0, prompt_texture_rect_map[prompt_window_id]->w, prompt_texture_rect_map[prompt_window_id]->h, 32, rmask, gmask, bmask, amask);
	/* optional do not understand yet */
	//propmt_background_surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);

	if (propmt_background_surface == NULL)
	{
		if (Developer::GetInstance()->is_debug_mode())
		{
			std::cout << "PromptWindow::CreateBackGroundTexture, SDL_CreateRGBSurface error - " << SDL_GetError() << std::endl;
		}
		return false;
	}

	// alter

	//color the surface . lol forgot to do it before

	SDL_FillRect(propmt_background_surface, NULL, SDL_MapRGB(propmt_background_surface->format, 84, 13, 110 ));

	//change surface to texture
	prompt_background_texture = SDL_CreateTextureFromSurface(passed_renderer, propmt_background_surface);

	if (prompt_background_texture == NULL) 
	{
		if (Developer::GetInstance()->is_debug_mode())
		{
			std::cout << "PromptWindow::CreateBackGroundTexture, SDL_CreateTextureFromSurface error - "<< SDL_GetError() << std::endl;
		}
		return false;
	}

	//set texture rect of prompt texture

	
		
	//record key

	

	// add values to map
	prompt_texture_map[prompt_window_id] = prompt_background_texture;

	

	return true;
}
//float % , do math round
bool PromptWindow::CreatePromptText(unsigned int passed_percent_x, unsigned int passed_percent_y,std::string passed_text_id, std::string passed_message, unsigned int text_size)
{

	if ((passed_percent_x < 1) || (passed_percent_y < 1))
	{
		passed_percent_x = 10;
		passed_percent_y = 10;
	}

	unsigned int arg_x = prompt_texture_rect_map[prompt_window_id]->x + ( round( prompt_texture_rect_map[prompt_window_id]->w * ( static_cast<float>(passed_percent_x) /100) ) );

	unsigned int arg_y = prompt_texture_rect_map[prompt_window_id]->y + ( round( prompt_texture_rect_map[prompt_window_id]->h * ( static_cast<float>(passed_percent_y) / 100) ));

	LoaderParams* pParams = new LoaderParams(arg_x, arg_y,10,10, passed_text_id);

	

	GameText* game_text_buffer = new GameText(pParams, passed_message, text_size);

	
	//game_texts_map[game_text_buffer->GetGameObjectID()] = game_text_buffer;
	game_texts_vector.push_back(game_text_buffer);

	
	return true;
}