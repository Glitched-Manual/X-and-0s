#include <iostream>
#include <vector>
#include <string>

class Position{
public:
int x;
int y;
};

class Win_Case{
Position combination[3];
std::string win_case_id;
public:
void SetPositionCombination();
Position* GetCombination(){ return combination; }
std::string GetWinCaseID(){ return win_case_id; }
};

void Win_Case::SetPositionCombination()
{
}

class Tile{
Position tile_position;
bool tile_marked;
std::string tile_mark;
public:
void SetTilePosition(int passed_x, int passed_y);
Position GetTilePosition(){return tile_position;}
};
void Tile ::SetTilePosition(int passed_x, int passed_y)
{
tile_position.x = passed_x;
tile_position.y = passed_y;
}


class Grid{
Tile game_tiles[3][3];
public:
//what?
void SetGameTile(int passed_x, int passed_y);
Tile GetGameTiles(int passed_x, int passed_y){return game_tiles[passed_x][passed_y];}
};

void Grid::SetGameTile(int passed_x, int passed_y)
{
   if((passed_x < 3)&(passed_y < 3))
   {
    game_tiles[passed_x][passed_y].SetTilePosition(passed_x,passed_y);
   }
}

class Game{
bool gameover;
Grid game_grid;
Win_Case win_cases[8];
public:
Grid GetGameGrid(){ return game_grid;}
void PlayerWin(Position passed_position);
void LoadWinCases();
};
void LoadWinCases()
{
//win_cases[0].
}

void Game::PlayerWin(Position passed_position)
{
//get play position -> passed_position

//check win cases if position is included

//check win case if all three positions are marked by player

//if all three marked by player
}
/*
int arr[3][1];
*/

int main()
{
Game game;
 
game.GetGameGrid().SetGameTile(0,0);
std::cout << "it works" << std::endl;
return 0;
}
