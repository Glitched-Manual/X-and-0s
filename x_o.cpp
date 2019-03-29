#include <iostream>
#include <vector>
#include <string>

typedef class{
public:
int x;
int y;
}Position;

class Tile{
Position tile_position;
bool tile_marked;
std::string tile_mark;
public:
Position GetTilePosition(){return tile_position;}
};

class Grid{
Tile game_tiles[3][3];
public:
Tile GetGameTile(int passed_x,int passed_y){return game_tiles[passed_x][passed_y];}
};
class GameLoop{
Grid game_grid;
public:
Grid GetGameGrid(){ return game_grid;}
};
int main()
{

std::cout << "it works" << std::endl;
return 0;
}
