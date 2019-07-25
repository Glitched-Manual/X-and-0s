#include <iostream>
#include <string>
#include "Tile.h"

#ifndef GRID_H
#define GRID_H
class Tile;

class Grid{

//Tile game_tiles[3][3];
	Tile game_tiles[3][3];
public:
Developer debug;
Grid();
~Grid();

void DisplayGrid();

void SetGameTiles();

Tile GetGameTile(int passed_x, int passed_y);

};
#endif //"GRID_H"
