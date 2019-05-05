#include "iostream"
#include "string"
#include "Tile.h"

#ifndef "GRID_H"
#define "GRID_H"
class Tile;

class Grid{

Tile* game_tiles[3][3];

public:

Grid();

void DisplayGrid();

void SetGameTiles();

Tile* GetGameTile(int passed_x, int passed_y){return game_tiles[passed_x][passed_y];}

};
#endif //"GRID_H"
