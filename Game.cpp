#include "Game.h"

Game::Game()
{
total_turns = 0;
Player* player_pos_1 = new Player;
Player* player_pos_2 = new Player;
game_grid = new Grid;
Game_Over = false;
quit = false;
}

Game::~Game()
{
delete player_pos_1;
delete player_pos_2;
delete game_grid;

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
	Position position_to_mark_obj;
    
	//input Player.GetInput # non sdl version

std::string p1_input = player_pos_1->GetPlayerInput(&quit);
 if(quit) break;
      if(FilterUserInput(p1_input,position_to_mark_obj))
       {
        //check if player can mark square
        if(CheckIfTileIsAvailable(position_to_mark_obj))
	{
        //mark square if available
	  SetTileMark(position_to_mark_obj);
	//total_turns++; caused endless loop other comment stuck on other players turn
	}
       }
     }
        //turn 2 Player* pos or AI - ai inherits player class
    else
     {
      //total_turns++;
     }
   //check for win if total_turns > 4
   //total_turns++; add to true case of if square available case
    if(total_turns > 4)
     {
       //scan through list of win cases for match. trigger Game_Over if match is found

     }  
}

  
}
//lol forgot to chach from bool to void
void Game::SetTileMark(Position position_to_mark)
{
GetGameGrid()->GetGameTile(position_to_mark.x,position_to_mark.y).SetTileMark("$");


}

bool Game::CheckIfTileIsAvailable(Position passed_position_to_check)
{

if((GetGameGrid()->GetGameTile(passed_position_to_check.x,passed_position_to_check.y).GetTIleIsMarkedStatus()) == true)
{
std::cout << "Game::CheckIfTileIsAvailable error tile is already marked" << std::endl;
return false;
}

return true;
}

bool Game:: FilterUserInput(std::string raw_input_string,Position& passed_position)
{



int x_pos = 0;
int y_pos = 0;
unsigned int mode = 0;
bool filter_successful = false;
enum axis{x_cord,y_cord};

for(unsigned int ind=0; ind < raw_input_string.length(); ind++)
{      
    if(raw_input_string[ind] =='x')
    {
     mode = y_cord;     
    }
    if(isdigit(raw_input_string[ind])){
        
        if(mode == x_cord)
        {
            x_pos = (x_pos*10)+(char(raw_input_string[ind]) - 48);
        }
        else
        {
           y_pos  = (y_pos*10)+(char(raw_input_string[ind]) - 48);
           if(!filter_successful)
	   {
	   filter_successful = true;
	   }	
        }
    }  
}
//std::cout << x_pos <<"," << y_pos <<std::endl;

if((mode == y_cord)&(filter_successful))
{

 if((x_pos < 3)&(y_pos < 3))
   {
    passed_position.x = x_pos;
    passed_position.y = y_pos;
   }
 else
   { 
    std::cout << "Game.cpp FilterUserInput error: (x_pos < 3)&(y_pos < 3) found false" << std::endl;
    return false;
   }
}
else
{
std::cout << "Game.cpp FilterUserInput error: (mode == y_cord)&(filter_successful) found false" << std::endl;
return false;
}


return true;
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

