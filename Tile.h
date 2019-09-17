#include <iostream>
#include <string>
#include "Position.h"

#ifndef TILE_H
#define TILE_H
class Position;
struct Developer;

class Tile{

Position* tile_position;

bool* tile_is_marked;

std::string* tile_mark;

public:

Tile();
~Tile();

// sets mark on tile , sets marked status to true
void SetTileMark(std::string passed_mark){ *tile_mark = passed_mark; *tile_is_marked = true;}

std::string* GetTileMark(){ return tile_mark; }

bool* GetTileIsMarkedStatus(){ return tile_is_marked;}
bool ReturnTileIsMarkedStatus() { return *tile_is_marked; }
void SetTilePosition(int passed_x, int passed_y);

Position* GetTilePosition(){return tile_position;}

void ResetTileAttributes();

};
#endif //TILE_H
