#include "TileMarker.h"



TileMarker::TileMarker(LoaderParams* pParams)
{
	tile_marker_rect = new SDL_Rect;
	texture_crop_rect = new SDL_Rect;


	tile_marker_rect->x = pParams->GetX() - (pParams->GetWidth() / 2);
	tile_marker_rect->y = pParams->GetY() - (pParams->GetHeight() / 2);
	tile_marker_rect->w = pParams->GetWidth();
	tile_marker_rect->h = pParams->GetHeight();

	texture_crop_rect->x = 0;
	texture_crop_rect->y = 0;

	texture_crop_rect->w = tile_marker_rect->w;
	texture_crop_rect->h = tile_marker_rect->h;
}

//this constructor is needed 

TileMarker::TileMarker(LoaderParams* pParams, Grid* passed_grid, Player* passed_player, SDL_Rect* Passed_hash_table_rect)
{
	tile_marker_rect = new SDL_Rect;
	texture_crop_rect = new SDL_Rect;


	tile_marker_rect->x = pParams->GetX() - (pParams->GetWidth() / 2);
	tile_marker_rect->y = pParams->GetY() - (pParams->GetHeight() / 2);
	tile_marker_rect->w = pParams->GetWidth();
	tile_marker_rect->h = pParams->GetHeight();

	texture_crop_rect->x = 0;
	texture_crop_rect->y = 0;

	texture_crop_rect->w = tile_marker_rect->w;
	texture_crop_rect->h = tile_marker_rect->h;

	//passed address to grid ptr

	game_grid_obj = passed_grid;

	player_obj = passed_player; // may not need

	hash_table_rect = Passed_hash_table_rect;
}




bool TileMarker::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{

	//load texture
	//tile_marker_texture = NULL;
	tile_marker_texture = IMG_LoadTexture(passed_Renderer, "resources/images/Drill mark blue.png");

	if (tile_marker_texture == NULL)
	{

		if (debug.is_debug_mode())
		{
			std::cout << "TileMarker::LoadGameObjectContent() error - " << IMG_GetError() << std::endl;
		}

		return false;
	}




	tile_marker_texture_player2 = IMG_LoadTexture(passed_Renderer, "resources/images/manual18 mark.png");

	if (tile_marker_texture_player2 == NULL)
	{

		if (debug.is_debug_mode())
		{
			std::cout << "TileMarker::LoadGameObjectContent() error - " << IMG_GetError() << std::endl;
		}

		return false;
	}


	if (debug.is_debug_mode())
	{
		std::cout << "TileMarker " << tile_marker_id << " was loaded!" << std::endl;
	}


	tile_marker_content_loaded = true;
	return true;
}

void TileMarker::Draw(SDL_Renderer* passed_Renderer)
{
	/*
	loop through all marked positions

	store marked positions

	insert position into rect to place mark in the correct place

	clip texture so only one frame is shown

	*/
	// draw in each tile the player marks

	//center hash
	/*

	   1          2
		----------
	   |          |
	   |          |
	   |          |
	   |          |
		----------
	  3           4

	  1 - (hash_table_rect->x),(hash_table_rect->y)
	  2 - (hash_table_rect->x) + (mark_rect->w),(hash_table_rect->y)
	  3 - (hash_table_rect->x), (hash_table_rect->y) + (mark_rect->h)
	  4 - (hash_table_rect->x) + (mark_rect->w), (hash_table_rect->y) + (mark_rect->h)




	*/
	/*
		 Center tile

		tile_marker_rect->x = ((hash_table_rect->x) + ((hash_table_rect->w) /2)) - (tile_marker_rect->w /2);
			tile_marker_rect->y = ((hash_table_rect->y) + ((hash_table_rect->h) / 2)) - (tile_marker_rect->h / 2);

			*/

			/*
			  Formula for centering image to each tile in hash table


			  make sure loop x is 0 - 2
			  pos_rect.x =( (origin_pos_x) + ( (total_width /6) + ( ((total_width /6) * 2 ) ) * loop_x )) - (image_rect.w / 2);

			  */
			  /*

			  if
		  player_pos_1->SetPlayerMark("!");
		  player_pos_2->SetPlayerMark("#");

		  render text based on previous symbols

			  */

	for (unsigned int cordinate_x = 0; cordinate_x < 3; cordinate_x++)
	{
		tile_marker_rect->x = ((hash_table_rect->x) + ((hash_table_rect->w / 6) + (((hash_table_rect->w / 6) * 2)) * cordinate_x)) - (tile_marker_rect->w / 2);


		for (unsigned int cordinate_y = 0; cordinate_y < 3; cordinate_y++)
		{


			tile_marker_rect->y = ((hash_table_rect->y) + ((hash_table_rect->h / 6) + (((hash_table_rect->h / 6) * 2) * cordinate_y))) - (tile_marker_rect->h / 2);

			//if mark == "!" || mark == "#"
			/*
			*game_grid_obj->GetGameTile(cordinate_x, cordinate_y).GetTileMark() //old way

			*game_grid_obj->GetGameTilePtr(cordinate_x, cordinate_y)->GetTileMark(); //patch deleted , and reapplied

			lol my message for getGameTiles() was shown. I thought
			*/
			//the grid call - creates and destroys grid objects. Wrong :p. re edit I was right keep patch
			if (*game_grid_obj->GetGameTilePtr(cordinate_x, cordinate_y)->GetTileMark() == "!")
			{
				SDL_RenderCopyEx(passed_Renderer, tile_marker_texture_player2, texture_crop_rect, tile_marker_rect, 0, NULL, SDL_FLIP_NONE);

			}

			if (*game_grid_obj->GetGameTilePtr(cordinate_x, cordinate_y)->GetTileMark() == "#")
			{
				SDL_RenderCopyEx(passed_Renderer, tile_marker_texture, texture_crop_rect, tile_marker_rect, 0, NULL, SDL_FLIP_NONE);

			}

			
			
		}

	}










}

void TileMarker::Update()
{

}

void TileMarker::CleanGameObjectContent()
{

}

void TileMarker::ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void TileMarker::AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void TileMarker::RevertAlteredTextureColor()
{

}

void TileMarker::SetOriginalColors()
{

}