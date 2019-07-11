#include <iostream>

#include <vector>

#include <string>
#include <memory>
#include "Position.h"
#include "Win_Case.h"
#include "Tile.h"
#include "Grid.h"
#include "Player.h"
#include "AI.h"
#include "Game.h"


int main()
{
//create method that calls everything - create obj by after declaration
Game* game = new Game;
//std::unique_ptr<Game> game;
 
//game = = std::make_unique<Game>(new Game);

//StartGame Method



game->SelectGameMode();
/*
1.Call start game method 

2.Select game mode - within startGame


3.Start using desired game loop

game->GameLoop();

4.End game ask if user wnts to play again - if yes clear required data start from 1
       

*/



return 0;

}

