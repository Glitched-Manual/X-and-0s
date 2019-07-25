#include <iostream>

#include <vector>

#include <string>

#include "Position.h"
#include "Win_Case.h"
#include "Tile.h"
#include "Grid.h"
#include "Player.h"
#include "AI.h"
#include "Game.h"


int main(int argc, char* args[])
{


Game* game;

game = new Game;
//Player p1;
//p1.SetPlayerMark("N");
//std::cout << p1.GetPlayerMark() << std::endl;
game->GameLoop();
/*
game->GetGameGrid()->SetGameTiles();

game->GetGameGrid()->DisplayGrid();

//set tile mark
game->GetGameGrid()->GetGameTile(1,0).SetTileMark("$");

std::cout << "\nGet mark test result : " << game->GetGameGrid()->GetGameTile(1,0).GetTilePosition()->x <<", " << game->GetGameGrid()->GetGameTile(1,0).GetTilePosition()->y <<"\n" << std::endl;
//display changed grid - did not work

game->GetGameGrid()->DisplayGrid();

//std::cout << "it works" << std::endl;

// did not change as expected. Changing to objects to pointers caused a segmentation fault
*/
std::cin.get();
return 0;

}

