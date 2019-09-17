#include "GameObject.h"
#include "Grid.h"
#include "Player.h"
#ifndef TILEMARKER_H
#define TILEMARKER_H

class TileMarker:public GameObject
{
	SDL_Texture* tile_marker_texture = NULL;
	SDL_Texture* tile_marker_texture_player2 = NULL; // shares rect values as other

	std::string tile_marker_id;
	bool tile_marker_content_loaded = false;
	Color tile_marker_original_color;
	bool tile_marker_colors_altered = false;

	SDL_Rect* tile_marker_rect = NULL;
	SDL_Rect* texture_crop_rect = NULL;
	

	SDL_Rect* hash_table_rect = NULL;

	// sent address of grid to draw marks in the proper place
	Grid* game_grid_obj;
    Player* player_obj; //use hard code symbols instead of player oject

protected:

public:
	TileMarker(LoaderParams* pParams);

	// grid player symbol and player address

	/*
    LoaderParams - quick loading

	Grid - get tiles data
	Player - get players mark
	SDL_Rect hash_table_rect - Get Hash Table Textures position for rendering

	*/
	TileMarker(LoaderParams* pParams, Grid* passed_grid, Player* passed_player, SDL_Rect* Passed_hash_table_rect);


	

	std::string GetGameObjectID() { return tile_marker_id; }
	bool LoadGameObjectContent(SDL_Renderer* passed_Renderer);
	void Draw(SDL_Renderer* passed_Renderer);
	void Update();
	void CleanGameObjectContent();

	 bool GetContentLoadedStatus() { return tile_marker_content_loaded; }
	 SDL_Texture* GetGameTexture() { return tile_marker_texture; }

	//if case switches colors for original to other colors and back when recalled
	 void ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);

	 void AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	 void RevertAlteredTextureColor();
	 void SetOriginalColors();

	 Color GetOringinalColors() { return tile_marker_original_color; }
	 bool GetAreColorsAltered() { return tile_marker_colors_altered; }
	 SDL_Rect* GetTextureRect() { return tile_marker_rect;           }

};

#endif //TILEMARKER_H