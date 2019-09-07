#include <iostream>
#include <string>
#include "Tile.h"
#include "GameObject.h"

#ifndef GRID_H
#define GRID_H
class Tile;
class GameObject;

class Grid 
{

//Tile game_tiles[3][3];
	Tile game_tiles[3][3];

	SDL_Texture* game_grid_texture;

	bool object_content_loaded = false;

public:
	
	
	Grid();
	~Grid();
Developer debug;

void DisplayGrid();

void SetGameTiles();

Tile GetGameTile(int passed_x, int passed_y);

Tile* GetGameTilePtr(int passed_x, int passed_y);


//load image



//render
void Draw(SDL_Renderer* passed_Renderer);
//update
void Update();
//clean
void CleanGameObjectContent();

bool GetContentLoadedStatus() { return object_content_loaded; }

//Reset tiles for rematch
void ResetAllTileAttributes();


protected:
	
};
#endif //GRID_H
