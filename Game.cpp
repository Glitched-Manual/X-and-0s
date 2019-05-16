#include "Game.h"

Game::Game()
{
total_turns = 0;
player_pos_1 = new Player; //lol fully redeclared before going out out scope or passing value into args cause segmentation errors
player_pos_2 = new Player;
game_grid = new Grid;

for(int wc=0;wc<8;wc++)
{
 win_cases[wc] = new Win_Case;
}
Game_Over = false;
quit = false;
win_cases_loaded = false;
player_pos_1->SetPlayerMark("!");
player_pos_2->SetPlayerMark("#");
LoadWinCases();
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
	int p1_turn = PlayerTurn(player_pos_1);

       if(p1_turn == 0) break;
     }
        //turn 2 Player* pos or AI - ai inherits player class
    else
     {
      int p2_turn = PlayerTurn(player_pos_2);

       if(p2_turn == 0) break;
     }
   //check for win if total_turns > 4
   //total_turns++; add to true case of if square available case
    if(total_turns > 4)
     {
       //scan through list of win cases for match. trigger Game_Over if match is found
       // if player 2 turn is next
      if(total_turns % 2 == 0)
        {
           // bool check if player1 won
        if(PlayerWin(player_pos_1))
           {
            Game_Over = true;
          }
        }
      else if(total_turns % 2 == 1)
        {
          // bool check if player2 won
	   if(PlayerWin(player_pos_2))
           {
            Game_Over = true;
          }
        }                 
     }  
    if((total_turns > 8)&&(Game_Over == false)){
      //Draw case

      Game_Over = true;
     std::cout << "Draw!" << std::endl;
     }
}

  
}
//returns status codes 
/*
0 - quit
1 - success
2 - value failure
3 - already marked
4 - blank input
*/
int Game::PlayerTurn(Player* current_player)
{
        //get input, check, mark if tile is available
  Position position_to_mark_obj;    

	//input Player.GetInput # non sdl version

     std::string p1ayer_input = current_player->GetPlayerInput(&quit);
  if(quit)
    {
	return 0;
    }
  else if(p1ayer_input == "")
    {
   std::cout << "No input found. Please enter a position example \"1x1\"" << std::endl;
   
        return 4;
    }
      if(FilterUserInput(p1ayer_input,position_to_mark_obj))
       {
        //check if player can mark square
          if(CheckIfTileIsAvailable(position_to_mark_obj))
	  {
           //mark square if available
           SetTileMark(position_to_mark_obj,*current_player->GetPlayerMark());//triggers segmentation error
	   total_turns++; //caused endless loop other comment stuck on other players turn
          }
        }
 return 1;
}

//lol forgot to change the type from bool to void
//add player_obj to get players mark
void Game::SetTileMark(Position position_to_mark,std::string player_mark)
{

GetGameGrid()->GetGameTile(position_to_mark.x,position_to_mark.y).SetTileMark(player_mark);

//current_player.GetPlayerMark(); causes segmentation error
}

bool Game::CheckIfTileIsAvailable(Position passed_position_to_check)
{

if((*GetGameGrid()->GetGameTile(passed_position_to_check.x,passed_position_to_check.y).GetTIleIsMarkedStatus()) == true)
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
win_cases[0]->SetWinCaseCombination(Position(0,0),Position(1,0),Position(2,0));
win_cases[1]->SetWinCaseCombination(Position(0,1),Position(1,1),Position(2,1));
win_cases[2]->SetWinCaseCombination(Position(0,2),Position(1,2),Position(2,2));
win_cases[3]->SetWinCaseCombination(Position(0,0),Position(0,1),Position(0,2));
win_cases[4]->SetWinCaseCombination(Position(1,0),Position(1,1),Position(1,2));
win_cases[5]->SetWinCaseCombination(Position(2,0),Position(2,1),Position(2,2));
win_cases[6]->SetWinCaseCombination(Position(0,0),Position(1,1),Position(2,2));
win_cases[7]->SetWinCaseCombination(Position(2,0),Position(1,1),Position(0,2));

win_cases_loaded = true;

}

Win_Case* Game::GetWincase(int win_case_index)
{

if(win_case_index > 7)
{
 win_case_index = win_case_index % 8;
}

}

bool Game::PlayerWin(Player* passed_player)
{


//check win cases if a player has won


//if true fink out which player won by the marks
 // make sure both payers do not have the same mark
int mark_true_case = 0;

  for(int wincase_index = 0; wincase_index <8; wincase_index++)
  {
   mark_true_case = 0;

    for(int wincase_combination_index = 0; wincase_combination_index <3; wincase_combination_index++)
     {
       if(*passed_player->GetPlayerMark() == *GetGameGrid()->GetGameTile(GetWincase(wincase_index)->GetCombination(wincase_combination_index).x,GetWincase(wincase_index)->GetCombination(wincase_combination_index).y).GetTileMark())  
        {
           mark_true_case++;
        }

     }	
      // check if three matches were found
    if(mark_true_case == 3)
      {
      // trigger wincase
       std::cout<< "Player "<< passed_player->GetPlayerMark() << " Wins!!"<< std::endl;
       return true;
      }
  } 
return false;
}

