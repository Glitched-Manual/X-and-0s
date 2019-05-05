#include <iostream>

#include <vector>

#include <string>

#include "Position.h"
#include "Win_Case.h"
#include "Tile.h"
#include "Grid.h"
#include "Player.h"
#include "AI.h"


int main()
{

Game game;
//game.GetGameGrid().SetGameTile(0,0);

game.GetGameGrid()->DisplayGrid();

//set tile mark
game.GetGameGrid()->GetGameTile(1,1)->SetTileMark("!");

std::cout << "\nGet mark test result : " << game.GetGameGrid()->GetGameTile(1,1)->GetTileMark()<< "\n" << std::endl;
// did not change as expected. Changing to objects to pointers caused a segmentation fault

game.GetGameGrid()->DisplayGrid();

//std::cout << "it works" << std::endl;

return 0;

}

