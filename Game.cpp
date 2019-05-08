#include "Game.h"

Game::Game()
{
total_turns = 0;
game_grid = new Grid;
Game_Over = false;
quit = false;
}

void Game::GameLoop()
{

//Game.turn non sdl2 redendering version use events to not delay rendering
  while((Game_Over == false)&&(quit == false))
  {
    GetGameGrid()->DisplayGrid();
	//turn 1 Player* pos1
    if (total_turns % 2 == 0)
     {
	//get input, check, mark if tile is available
     }
        //turn 2 Player* pos or AI - ai inherits player class
    else
     {

     }
   //check for win if total_turns > 4
   total_turns++;
    if(total_turns > 4)
     {
       //scan through list of win cases for match. trigger Game_Over if match is found

     }  
}

  
}

void Game::LoadWinCases()
{

//win_cases[0].

}


bool Game::PlayerWin()

{


//check win cases if a player has won


//if true fink out which player won by the marks
 // make sure both payers do not have the same mark

}

