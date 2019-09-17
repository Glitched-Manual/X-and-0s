#include "TileSelector.h"

TileSelector::TileSelector(LoaderParams* pParams, Grid* passed_grid, SDL_Rect* passed_hash_table_rect, CSDL* passed_csdl_obj, std::string passed_id_name)
{
	tile_selector_texture_rect = new SDL_Rect;

	selector_position = new Position;
	time_Check = SDL_GetTicks();
	//LoaderParams

	tile_selector_texture_rect->x = pParams->GetX() - (pParams->GetWidth() / 2);
	tile_selector_texture_rect->y = pParams->GetY() - (pParams->GetHeight() / 2);
	tile_selector_texture_rect->w = pParams->GetWidth();
	tile_selector_texture_rect->h = pParams->GetHeight();

	//get grid obj
	     
	 game_grid = passed_grid;

	//get hash table rect

	 hash_table_rect = passed_hash_table_rect;

	 //get csdl obj by pointer

	 csdl_obj = passed_csdl_obj;

	//set string id name

	 tile_selector_id = passed_id_name;

	  mouse_pos_x = new int;

	  mouse_pos_y = new int;


	  *mouse_pos_x = 0;

	  *mouse_pos_y = 0;
	 // current_game_controls = game_controller_controls;
	  current_game_controls = mouse_controls;
}



bool TileSelector::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{
	//open image
	tile_selector_texture = IMG_LoadTexture(passed_Renderer, "resources/images/crosshair_image.png");

	if (tile_selector_texture == NULL)
	{

		if (debug.is_debug_mode())
		{
			std::cout << "TileSelector::LoadGameObjectContent() error - " << IMG_GetError() << std::endl;
		}
		return false;
	}

	// positions of tiles from hash table

	// do math on draw for dynamic postions

	//set colors red ,blue,green or black or white

	tile_selector_content_loaded = true;

	return true;

}
void TileSelector::Draw(SDL_Renderer* passed_Renderer)
{

	/*
	
	if mouse draw using Uint32 SDL_GetMouseState(int* x, int* y);

	*/
	
		if (current_game_controls == mouse_controls)
		{
			tile_selector_texture_rect->x = *mouse_pos_x - (tile_selector_texture_rect->w / 2);
			tile_selector_texture_rect->y = *mouse_pos_y - (tile_selector_texture_rect->h / 2);
		}
		else if (current_game_controls == game_controller_controls)
		{
			tile_selector_texture_rect->x = *mouse_pos_x - (tile_selector_texture_rect->w / 2);
			tile_selector_texture_rect->y = *mouse_pos_y - (tile_selector_texture_rect->h / 2);
		}

		if (tile_selector_content_loaded)
		{
			SDL_RenderCopyEx(passed_Renderer, tile_selector_texture, NULL, tile_selector_texture_rect, 0, NULL, SDL_FLIP_NONE);
		}
	

	
}
void TileSelector::Update()
{
		
	/*
	
	Needs to change control types 
	  - if mouse moves on grid mouse control
	  - if controller button pressed controller
	  - if keyboard key keyboard arrows
	*/
	// do get ticks thing
	if (time_Check + 250 < SDL_GetTicks())
	{
		if (current_game_controls == mouse_controls)
		{
			SDL_GetMouseState(mouse_pos_x, mouse_pos_y);
			SetSelectorScreenPosition();//updates position of selector
		}
		else if (current_game_controls == game_controller_controls)
		{
			/*
			do controller selector direction changes here
			*/
			ButtonPressed();
			ButtonControls();
			ButtonReleased();

		}
		else if (current_game_controls == keyboard_controls)
		{
			/*
			do keyboard selector direction changes here
			*/
			ButtonPressed();
			ButtonControls();
			ButtonReleased();

		}
	        time_Check = SDL_GetTicks();
			SetSelectorScreenPosition();
	}
	/*
	if tile unavailable change color

	check tile if selector is over
	*/


}
void TileSelector::CleanGameObjectContent()
{

}


void TileSelector::ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void TileSelector::AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}
void TileSelector::RevertAlteredTextureColor()
{

}
void TileSelector::SetOriginalColors()
{

}

void TileSelector::LoadSelectorColors()
{
	
}

void TileSelector::SetSelectorScreenPosition()
{

	tile_selector_texture_rect->x = *mouse_pos_x;
		
	tile_selector_texture_rect->y = *mouse_pos_y;
}

void TileSelector::MoveSelector(int passed_x, int passed_y)
{
	/*tile_selector_texture_rect->x = passed_x;
	tile_selector_texture_rect->y = passed_y;

	*/

	*mouse_pos_x = passed_x;

	*mouse_pos_y = passed_y;
}

void TileSelector::ButtonControls()
{
	if (left_direction == true)
	{
		*mouse_pos_x -= 2;
	}

	if (right_direction == true)
	{
		*mouse_pos_x += 2;
	}

	if (up_direction == true)
	{
		*mouse_pos_y -= 2;
	}

	if (down_direction == true)
	{
		*mouse_pos_y += 2;
	}
}

void TileSelector::SetDirectionTrue(std::string passed_direction)
{
	if (passed_direction == "UP")
	{
		up_direction = true;
	}

	else if (passed_direction == "DOWN")
	{
		down_direction = true;
	}

	else if (passed_direction == "LEFT")
	{
		left_direction = true;
	}

	else if (passed_direction == "RIGHT")
	{
		right_direction = true;
	}
}

void TileSelector::SetDirectionFalse(std::string passed_direction)
{

	if (passed_direction == "UP")
	{
		up_direction = false;
	}

	else if (passed_direction == "DOWN")
	{
		down_direction = false;
	}

	else if (passed_direction == "LEFT")
	{
		left_direction = false;
	}

	else if (passed_direction == "RIGHT")
	{
		right_direction = false;
	}

}





/*
			if A button pressed

			hit box gives value to sting input ie: 2x2 or 0x1
			*/
			//if mouse click within a tile hit box


	

void TileSelector::ButtonPressed()
{
	/*

	Move Selector arrow keys and controller
	*/
	//if sdl pressed


	

	if (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)
	{

		if (csdl_obj->ButtonInputCheck("UP"))
		{
			up_direction = true;
		}

		if (csdl_obj->ButtonInputCheck("DOWN"))
		{
			down_direction = true;
		}

		

		if (csdl_obj->ButtonInputCheck("LEFT"))
		{
			left_direction = true;
		}

		if (csdl_obj->ButtonInputCheck("RIGHT"))
		{
			right_direction = true;
						
		}
		if (debug.is_debug_mode())
		{

			
			std::cout << "Directional button Pressed " << std::endl;
			std::cout << "The selector is now located at " << mouse_pos_x << "," << mouse_pos_y << std::endl;
		}
	}
}


void TileSelector::ButtonReleased()
{

	/*
	if released version

	ButtonPressedCheck()

	ButtonReleasedCheck()
				*/

	if (csdl_obj->GetSDLGameEvent()->type == SDL_KEYUP)
	{
		

		if (csdl_obj->ButtonInputCheck("UP"))
		{
			up_direction = false;
		}

		if (csdl_obj->ButtonInputCheck("DOWN"))
		{

			down_direction = false;
		}

		if (csdl_obj->ButtonInputCheck("LEFT"))
		{
			left_direction = false;
		}

		if (csdl_obj->ButtonInputCheck("RIGHT"))
		{
			right_direction = false;

			/*	if (debug.is_debug_mode())
				{
					std::cout << "The selcetor is now located at " << game_tile_selector->GetX() << "," << game_tile_selector->GetY() << std::endl;
				}
				*/
		}

		if (debug.is_debug_mode())
		{
			std::cout << "Directional button Released " << std::endl;
		}
	}
}
