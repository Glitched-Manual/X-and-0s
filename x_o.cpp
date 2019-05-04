#include <iostream>

#include <vector>

#include <string>

#include "Position.h"

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

Tile();
void SetTileMark(std::string passed_mark){ tile_mark = passed_mark;}

std::string GetTileMark(){ return tile_mark; }

void SetTilePosition(int passed_x, int passed_y);

Position GetTilePosition(){return tile_position;}

};

Tile::Tile()
{
tile_mark = "?";
}

void Tile ::SetTilePosition(int passed_x, int passed_y)

{

tile_position.x = passed_x;

tile_position.y = passed_y;

}



class Grid{

Tile game_tiles[3][3];

public:

Grid();

void DisplayGrid();

void SetGameTiles();

Tile GetGameTile(int passed_x, int passed_y){return game_tiles[passed_x][passed_y];}

};

Grid ::Grid()
{
    SetGameTiles();
}

void Grid::SetGameTiles()
{ 
    for(unsigned int yi = 0; yi < 3; yi++)
    {
        for(unsigned int xi = 0; xi < 3; xi++)
        {
             game_tiles[xi][yi].SetTilePosition(xi,yi);
        }
    }
}

void Grid::DisplayGrid()
{
/*

 x | x | x |\n
 ---------- \n
 x | x | x |\n
 ---------- \n
 x | x | x |\n
*/


for(unsigned int yi = 0; yi < 3; yi++)
    {
        for(unsigned int xi = 0; xi < 3; xi++)
        {
            // game_tiles[xi][yi].SetTilePosition(xi,yi);
           std::cout << " " << GetGameTile(xi,yi).GetTileMark() << " |";
          //if x == 2 add "\n" and "-----\n"  
          if(xi==2)
	  {
	   std::cout<< "\n ----------\n";
	  }
        }
    }
  std::cout<< "\n";
}

class Player{

};

class AI{

};

class Game{

bool Game_Over;

Grid game_grid;

Win_Case win_cases[8];
unsigned int turn_phase;
public:
Game();

Grid GetGameGrid(){ return game_grid;}
int GetTurnPhase(){ return turn_phase; }
void PlayerWin(Position passed_position);

void LoadWinCases();

void GameLoop();

};
Game::Game()
{
Game_Over = false;
}

void Game::GameLoop()
{


  while((Game_Over == false))
  {
	//turn 1

        //turn 2
  }

}

void Game::LoadWinCases()
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
//game.GetGameGrid().SetGameTile(0,0);

game.GetGameGrid().DisplayGrid();

//set tile mark
game.GetGameGrid().GetGameTile(1,1).SetTileMark("!");

//display changed grid

game.GetGameGrid().DisplayGrid();

std::cout << "it works" << std::endl;

return 0;

}


