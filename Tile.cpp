#include "Tile.h"

Tile::Tile()
{
tile_mark = new std::string;
tile_position = new Position;
tile_is_marked = new bool;
*tile_is_marked = false;
*tile_mark = "?";
}

void Tile ::SetTilePosition(int passed_x, int passed_y)

{

tile_position->x = passed_x;

tile_position->y = passed_y;

}

