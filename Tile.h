#include "iostream"
#include "string"
#include "Position.h"

#ifndef "TILE_H"
#define "TILE_H"
class Position;

class Tile{

Position tile_position;

bool tile_marked;

std::string tile_mark;

public:

Tile();
void SetTileMark(std::string passed_mark){ tile_mark = passed_mark;}

std::string GetTileMark(){ return tile_mark; }

void SetTilePosition(int passed_x, int passed_y);

Position GetTilePosition(){return tile_position;}

};
#endif //TILE_H
