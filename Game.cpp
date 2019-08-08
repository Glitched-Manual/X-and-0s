#include "Game.h"

Game::Game(unsigned int passed_screen_width, unsigned int passed_screen_height)
{

SCREEN_WIDTH = passed_screen_width;
SCREEN_HEIGHT = passed_screen_height;

total_turns = 0;
player_pos_1 = new Player; //lol fully redeclared before going out out scope or passing value into args cause segmentation errors
player_pos_2 = new Player;
game_grid = new Grid; //add params
csdl_obj = new CSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
Game_Over = false;
quit_game_from_input = false;
win_cases_loaded = false;

player_pos_1->SetPlayerMark("!");
player_pos_2->SetPlayerMark("#");
LoadWinCases();
  
  if(debug.is_debug_mode())
  {
	  std::cout << "WinCases Loaded" << std::endl;
  }

  //init sdl
  csdl_obj->Init();
  x_o_game_state = main_menu;
  LoadGameOpeningMenu();
  LoadGameObjectContent();

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

	if (debug.is_debug_mode()) 
	{
		std::cout << "CSDL::init() call finished! Starting GameLoop!" << std::endl;

	}
	
	while ((csdl_obj->GetSDLGameEvent()->type != SDL_QUIT) && (quit_game_from_input == false))
	{
		/*if (debug.is_text_based_game())
		{
			//game_grid->DisplayGrid(); loops infinitly is a problem
		}
		*/
		SDL_RenderClear(csdl_obj->GetSDLRenderer());

		if (SDL_PollEvent(csdl_obj->GetSDLGameEvent()) > 0)
		{

			GameEventManager();
		}
		//render
		RenderGameTextures();
	    /*
		handle events

		key board and controller
		*/		
		
		//update


		//clean
		
		SDL_RenderPresent(csdl_obj->GetSDLRenderer());
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
  Position* position_to_mark_obj; 
  position_to_mark_obj = new Position;    

	//input Player.GetInput # non sdl version
    // get keyboard input from sdl2 convert numbers and char values
     std::string p1ayer_input = current_player->GetPlayerInput(&quit_game_from_input);
  if(quit_game_from_input)
    {
         delete position_to_mark_obj;
	return 0;
    }
  else if(p1ayer_input == "")//remove this
    {
   std::cout << "No input found. Please enter a position example \"1x1\"" << std::endl;
         delete position_to_mark_obj;
        return 4;
    }
      if(FilterUserInput(p1ayer_input,position_to_mark_obj))
       {
        //check if player can mark square
          if(CheckIfTileIsAvailable(position_to_mark_obj))
	  {
             std::cout << "check if available" << std::endl;
           //mark square if available
           SetGameTileMark(position_to_mark_obj,*current_player->GetPlayerMark());//triggers segmentation error
           std::cout << "Tile marked" << std::endl;
	   total_turns++; //caused endless loop other comment stuck on other players turn
          }
        }
      delete position_to_mark_obj;
 return 1;
}

//lol forgot to change the type from bool to void
//add player_obj to get players mark
void Game::SetGameTileMark(Position* position_to_mark,std::string player_mark)
{

GetGameGrid()->GetGameTile(*position_to_mark->GetX(),*position_to_mark->GetY()).SetTileMark(player_mark);

//current_player.GetPlayerMark(); causes segmentation error
}

bool Game::CheckIfTileIsAvailable(Position* passed_position_to_check)
{
std::cout << "Game::CheckIfTileIsAvailable  get position" << std::endl;
if((*GetGameGrid()->GetGameTile(*passed_position_to_check->GetX(),*passed_position_to_check->GetY()).GetTIleIsMarkedStatus()) == true)
{
	if (debug.is_debug_mode())
	{
		std::cout << "Game::CheckIfTileIsAvailable error tile is already marked" << std::endl;
	}

    return false;
}
if (debug.is_debug_mode())
{
	std::cout << "Game::CheckIfTileIsAvailable  get position success" << std::endl;
}

return true;
}

bool Game:: FilterUserInput(std::string raw_input_string,Position* passed_position)
{
	   
int x_pos = 0;
int y_pos = 0;
unsigned int mode = 0;
bool filter_successful = false;
enum axis{x_cord,y_cord};

for(unsigned int ind=0; ind < raw_input_string.length(); ind++)
{      
    if((raw_input_string[ind] =='x')|(raw_input_string[ind] =='X'))
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
/*
if (debug.is_debug_mode())
{
	std::cout << x_pos << "," << y_pos << std::endl;
}
*/

if((mode == y_cord)&(filter_successful))
{

 if((x_pos < 3)&(y_pos < 3))
   {
    passed_position->SetX(x_pos);
    passed_position->SetY(y_pos);
   }
 else
   { 
	 if (debug.is_debug_mode())
	 {
		 std::cout << "Game.cpp FilterUserInput error: (x_pos < 3)&(y_pos < 3) found false" << std::endl;
	 }
	     
    return false;
   }
}
else
{
	if (debug.is_debug_mode())
	{
		std::cout << "Game.cpp FilterUserInput error: (mode == y_cord)&(filter_successful) found false" << std::endl;
	}

return false;
}


return true;
}

void Game::LoadWinCases()
{
	if (debug.is_debug_mode())
	{
		std::cout << "LoadWinCase start" << std::endl;
	}
	int x = 0;
//fix win_cases
	//Win_Case* temp;

//temp = new Win_Case(new Position(0, 0), new Position(1, 0), new Position(2, 0)));
	//win_cases.push_back(temp);
	
	    win_cases[x].SetWinCaseCombination(Position(0,0),Position(1,0),Position(2,0));
		++x;
		win_cases[x].SetWinCaseCombination(Position(0,1),Position(1,1),Position(2,1));
		++x;
		win_cases[x].SetWinCaseCombination(Position(0,2),Position(1,2),Position(2,2));
		++x;
		win_cases[x].SetWinCaseCombination(Position(0,0),Position(0,1),Position(0,2));
		++x;
		win_cases[x].SetWinCaseCombination(Position(1,0),Position(1,1),Position(1,2));
		++x;
		win_cases[x].SetWinCaseCombination(Position(2,0),Position(2,1),Position(2,2));
		++x;
		win_cases[x].SetWinCaseCombination(Position(0,0),Position(1,1),Position(2,2));
		++x;
		win_cases[x].SetWinCaseCombination(Position(2,0),Position(1,1),Position(0,2));
		
		if (debug.is_debug_mode())
		{
			std::cout << "LoadWinCase End" << std::endl;

			std::cout << *win_cases[0].GetCombination(1)->GetX() << " , " << *win_cases[0].GetCombination(1)->GetY() << std::endl;
		}
		
      win_cases_loaded = true;

}

Win_Case Game::GetWinCase(int passed_win_case_index)
{

  if(passed_win_case_index > 7)
  {
	  passed_win_case_index = passed_win_case_index % 8;
  }

return win_cases[passed_win_case_index];
}

bool Game::PlayerWin(Player* passed_player)
{


//check win cases if a player has won
	if (debug.is_debug_mode())
	{
		std::cout << "check if player wins start" << std::endl;
    }
 
//if true fink out which player won by the marks
 // make sure both payers do not have the same mark


  for(int wincase_index = 0; wincase_index <8; wincase_index++)
  {
       int mark_true_case = 0;

    for(int wincase_combination_index = 0; wincase_combination_index <3; wincase_combination_index++)
     {
       if(*passed_player->GetPlayerMark() == *GetGameGrid()->GetGameTile(*GetWinCase(wincase_index).GetCombination(wincase_combination_index)->GetX(), *GetWinCase(wincase_index).GetCombination(wincase_combination_index)->GetY()).GetTileMark())
        {
           ++mark_true_case;
		   if (debug.is_debug_mode())
		   {
			   std::cout << "Marked case = " << mark_true_case << std::endl;
		   }
         
        }

     }	
      // check if three matches were found
    if(mark_true_case == 3)
      {
      // trigger wincase
		if (debug.is_debug_mode())
		{
			std::cout << "Player " << *passed_player->GetPlayerMark() << " Wins!!" << std::endl;
		}
     
       return true;
      }
  } 
return false;
}

void Game::MainGameMenu()
{
	/*
	load 
	
	images audio
	*/

	//run

	//close and clean


}
//fix after events and graphics

//call on click of keyboard input conditions met
void Game::TurnPhaseEvent()
{

	if (total_turns % 2 == 0)
	{
		int p1_turn = PlayerTurn(player_pos_1);

		//if (p1_turn == 0) break;
	}
	//turn 2 Player* pos or AI - ai inherits player class
	else
	{
		int p2_turn = PlayerTurn(player_pos_2);

		//if (p2_turn == 0) break;
	}
	//check for win if total_turns > 4
	//total_turns++; add to true case of if square available case
	if (total_turns > 4)
	{
		//scan through list of win cases for match. trigger Game_Over if match is found
		// if player 2 turn is next
		//check numbr matches other playrs turn messup earlier
		if (total_turns % 2 == 1)
		{
			// bool check if player1 won
			if (PlayerWin(player_pos_1))
			{
				std::cout << "Player 1 Wins!" << std::endl;
				Game_Over = true;
			}
		}
		else if (total_turns % 2 == 0)
		{
			// bool check if player2 won
			if (PlayerWin(player_pos_2))
			{
				std::cout << "Player 2 Wins!!" << std::endl;
				Game_Over = true;
			}
		}
	}
	if ((total_turns > 8) && (Game_Over == false)) {
		//Draw case

		Game_Over = true;
		std::cout << "Draw!" << std::endl;
	}
}

bool Game::LoadGameObjectContent()
{
	//GameObject* gameObjectHashTable = new HashTable(new LoaderParams(100,100,100,100,"HashTable"));
	//allGameObjects.push_back(gameObjectHashTable);


	//loop through allGameObjects vector to call the proper loading method
	if (!(allGameObjects.empty()))
	{

		for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
		{
			(*game_object_index)->LoadGameObjectContent(csdl_obj->GetSDLRenderer());
		}
		if (debug.is_debug_mode())
		{
			std::cout << "Game::LoadGameObjectContent() Objects loaded" << std::endl;
		}

	}
	else
	{
		if (debug.is_debug_mode())
		{
			std::cout << "Game::LoadGameObjectContent() Error - allGameObjects found empty!" << std::endl;
		}
		

		return false;
	}
	return true;
}


bool Game::LoadGameOpeningMenu()
{

	GameObject* start_menu_text = NULL;
	//x, y, width, height, std::string passed_textureID

	//center text pass center x and y
	start_menu_text = new GameText(new LoaderParams(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,100,100,"Start Game"));

	if(start_menu_text == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("Game::LoadGameOpeningMenu() SDL Error: %s\n", SDL_GetError());
			return false;
		}

	}
	
	allGameObjects.push_back(start_menu_text);

	if (debug.is_debug_mode())
	{
		std::cout << "Game::LoadGameOpeningMenu() was pushed to the allGameObjects vector" << std::endl;
	}

	return true;
}

void Game::RenderGameTextures()
{
	if (!(allGameObjects.empty()))
	{
		
		if (x_o_game_state == main_menu)
		{
			for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
			{
				if ((*game_object_index)->GetGameObjectID() =="Start Game")
				{
					(*game_object_index)->Draw(csdl_obj->GetSDLRenderer());
				}

				
			}
		}
		else //render everything! probably bad :P
		{
			for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
			{
				(*game_object_index)->Draw(csdl_obj->GetSDLRenderer());
			}

		}
		
	}
}

void Game::GameEventManager()
{
	

		if (csdl_obj->GetSDLGameEvent()->type == SDL_KEYUP)
		{
			std::cout << csdl_obj->GetSDLGameEvent()->key.keysym.sym << std::endl;
		}

		if(csdl_obj->GetSDLGameEvent()->type == SDL_CONTROLLERBUTTONDOWN )
		{
			if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				std::cout << " \"A\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				std::cout << " \"B\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_X)
			{
				std::cout << " \"X\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				std::cout << " \"Y\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_AXIS_LEFTX)
			{
				std::cout << " \"AXIS_LEFTX\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_AXIS_LEFTY)
			{
				std::cout << " \"AXIS_LEFTX\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_AXIS_RIGHTX)
			{
				std::cout << " \"AXIS_LEFTX\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_AXIS_RIGHTY)
			{
				std::cout << " \"AXIS_LEFTX\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
			{
				std::cout << " \"DPAD_UP\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			{
				std::cout << " \"DPAD_DOWN\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				std::cout << " \"DPAD_LEFT\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				std::cout << " \"DPAD_RIGHT\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE)
			{
				std::cout << " \"GUIDE\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_START)
			{
				std::cout << " \"START\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
			{
				std::cout << " \"LEFTSHOULDER\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
			{
				std::cout << " \"RIGHTSHOULDER\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_BACK)
			{
				std::cout << " \"BUTTON_BACK\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK)
			{
				std::cout << " \"LEFTSTICK\" was pressed!" << std::endl;
			}
			else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
			{
				std::cout << " \"RIGHTSTICK\" was pressed!" << std::endl;
			}
			else 
			{
				std::cout << csdl_obj->GetSDLGameEvent()->cbutton.button << std::endl;
			}
			
			
		}

	
}