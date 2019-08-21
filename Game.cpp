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

  //Load Main menu textures
  LoadGameOpeningMenu();

  //Load Options menu textures
  LoadGameOptionsMenu();
  // hash table and marks
  LoadGameplayObjects();
  loadPlayerTextureMarks(); // test version


  LoadGameObjectContent(); // loads all content in allGameObjects. put all game objects before this
 
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
		//SDL_SetRenderDrawColor(csdl_obj->GetSDLRenderer(), 167, 153, 183, 255 );

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
if((*GetGameGrid()->GetGameTile(*passed_position_to_check->GetX(),*passed_position_to_check->GetY()).GetTileIsMarkedStatus()) == true)
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

void Game::MainGameMenu() //not needed
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

bool Game::LoadGameplayObjects()
{
	GameObject* hash_table_game_obj = NULL;
	//load hash table
	HashTable* hash_table = new HashTable( new LoaderParams( SCREEN_WIDTH /2, SCREEN_HEIGHT /2,400,400,"Hash Table" ) );

	game_object_map["Hash Table"] = hash_table;
	hash_table_game_obj = hash_table;

	allGameObjects.push_back(hash_table_game_obj);

	//load marks

	return true;
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
			//loades textures and such
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
	start_menu_text = new GameText(new LoaderParams(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,100,100,"Start Game"),60);

	if(start_menu_text == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("Game::LoadGameOpeningMenu() SDL Error: %s\n", SDL_GetError());
			return false;
		}

	}
	
	game_object_map["Start Game"] = start_menu_text;
	allGameObjects.push_back(start_menu_text);

	if (debug.is_debug_mode())
	{
		std::cout << "Game::LoadGameOpeningMenu() was pushed to the allGameObjects vector" << std::endl;
	}

	return true;
}


//
bool Game::LoadGameOptionsMenu()
{
	/*
	
	Load text 

	Play       Options       Credits
	x-axis of width
<---25%----------50%----------75%-->

y axis 50% of height
	*/
	//play
	GameObject* game_options_menu_play_text = NULL;

	GameText* options_menu_play = new GameText(new LoaderParams((SCREEN_WIDTH / 5), SCREEN_HEIGHT / 2, 100, 100, "Play Button"), "Play", 30);

	game_options_menu_play_text = options_menu_play;

	game_object_map["Play Button"] = game_options_menu_play_text;
	allGameObjects.push_back(game_options_menu_play_text);

	//Options

	GameText* options_menu_options = new GameText(new LoaderParams(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, "Options Button"), "Options", 30);

	GameObject* game_options_menu_options_text = NULL;

	game_options_menu_options_text = options_menu_options;

	game_object_map["Options Button"] = game_options_menu_options_text;

	allGameObjects.push_back(game_options_menu_options_text);

	//Credits

	GameObject* game_options_menu_credits_text = NULL;

	GameText* options_menu_credits = new GameText(new LoaderParams((SCREEN_WIDTH / 5) * 4, (SCREEN_HEIGHT / 2) , 100, 100, "Credits Button"), "Credits", 30);

	
	game_options_menu_credits_text = options_menu_credits;

	game_object_map["Credits Button"] = game_options_menu_credits_text;

	allGameObjects.push_back(game_options_menu_credits_text);

	return true;
}

bool Game::loadPlayerTextureMarks()
{

	GameObject* player_tile_mark_gam_obj = NULL; // will need two one for each player

	//need rect* of hash table , make x and y change depending on maked tiles

	
	TileMarker* tile_marker_obj = new TileMarker(new LoaderParams((SCREEN_WIDTH /2), (SCREEN_HEIGHT / 2) , 100, 100, "test mark"),game_grid, player_pos_1, game_object_map["Hash Table"]->GetTextureRect()); // may only the player string mark is needed

	player_tile_mark_gam_obj = tile_marker_obj;

	

	game_object_map["test mark"] = tile_marker_obj; // did not use game object here

	allGameObjects.push_back(player_tile_mark_gam_obj); //pushed TileMark instead of game object lol

	if (debug.is_debug_mode())
	{
		std::cout << "Player mark loaded" << std::endl;
	}

	return true;
}


void Game::RenderGameTextures()
{
	if (!(allGameObjects.empty()))
	{
		
		if (x_o_game_state == main_menu)
		{
			//use map istead of for loop
			/*for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
			{
				if ((*game_object_index)->GetGameObjectID() =="Start Game")
				{
					(*game_object_index)->Draw(csdl_obj->GetSDLRenderer());
				}
				
			}
			*/
			
			game_object_map["Start Game"]->Draw(csdl_obj->GetSDLRenderer()); 
		}
		//Game options
		else if (x_o_game_state == game_options)
		{
			//Play

			game_object_map["Play Button"]->Draw(csdl_obj->GetSDLRenderer());

			//Options

			game_object_map["Options Button"]->Draw(csdl_obj->GetSDLRenderer());

			//Credits

			game_object_map["Credits Button"]->Draw(csdl_obj->GetSDLRenderer());

		}

		else if (x_o_game_state == gameplay)
		{

			//render grid
	    	game_object_map["Hash Table"]->Draw( csdl_obj->GetSDLRenderer() );

			//loop through marked tiles , render marks to proper spots
			game_object_map["test mark"]->Draw( csdl_obj->GetSDLRenderer() );

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
	if (csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED || csdl_obj->GetSDLGameEvent()->key.state == SDL_PRESSED)
	{


		//if at main menu
		if (x_o_game_state == main_menu)
		{
			//if keyboard or controller pressed


				//if start button or enter key pressed
			if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_START) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RETURN && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
			{
				if (debug.is_debug_mode())
				{
					std::cout << "\nYou Started the game!\n" << std::endl;
				}
				//rgb(38, 64, 139)
				game_object_map["Start Game"]->ToggleTextureColor(38, 64, 139);


				//create a change state to put values back to starting position
				x_o_game_state = game_options;
				//game_object_map["Start Game"]->AlterTextureColor( 38, 64, 139);
			}
		}


		// end of main_menu events


		else if (x_o_game_state == game_options)
		{



			// if none of Play Options or Credits Highlighted Highlight Play

			//if left key pressed or left button pressed highlight button left of the last, unless it is the left most button

			//check if any highlighted text present GetAreColorsAltered()

			// make sure not more than one is highlighted

			unsigned int total_text_highlighted = 0;

			std::string highlighed_Text;
			/*
			game_text_message = new char[passed_message.length() + 1];
			strcpy(game_text_message, passed_message.c_str());
			*/
			if (game_object_map["Play Button"]->GetAreColorsAltered())
			{
				highlighed_Text = game_object_map["Play Button"]->GetGameObjectID();
				total_text_highlighted++;
			}


			if (game_object_map["Options Button"]->GetAreColorsAltered())
			{
				highlighed_Text = game_object_map["Options Button"]->GetGameObjectID();
				total_text_highlighted++;
			}

			if (game_object_map["Credits Button"]->GetAreColorsAltered())
			{
				highlighed_Text = game_object_map["Credits Button"]->GetGameObjectID();
				total_text_highlighted++;
			}

			if (total_text_highlighted > 1)
			{
				// unhighlight everthing

				game_object_map["Play Button"]->RevertAlteredTextureColor();
				game_object_map["Options Button"]->RevertAlteredTextureColor();
				game_object_map["Credits Button"]->RevertAlteredTextureColor();

				x_o_highlighted_option = none_of_the_options_highlighted;

				if (debug.is_debug_mode())
				{
					std::cout << "\n All Buttons Buttons unhighlighted Highlighted \n" << std::endl;
				}
			}
			else if (total_text_highlighted = 0)
			{

				x_o_highlighted_option = none_of_the_options_highlighted;
			}
			else if (total_text_highlighted  < 0) 
			{
				total_text_highlighted = 0;
				x_o_highlighted_option = none_of_the_options_highlighted;
			}
			
			// SDL_CONTROLLER_BUTTON_DPAD_LEFT   or    SDL_CONTROLLER_BUTTON_DPAD_RIGHT
			// SDLK_LEFT  SDLK_RIGHT
			//none_of_the_options,play_option,options_option,credits_option
			switch (x_o_highlighted_option)
			{

			case  play_option_highlighted:
				//right command or click in hit box
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) || (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RIGHT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
				{
					//change x_o_highlighted_option  play_option_highlighted to options_option_highlighted
					x_o_highlighted_option = options_option_highlighted;
					// unhighlight play
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					// highlight options 38, 64, 139
					game_object_map["Options Button"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "\n Options Button Highlighted \n" << std::endl;
					}
				}
				// if b or esc pressed
				// SDLK_RETURN
				

				else if (( csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_START ) || (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_A ) || (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RETURN ) )
				{
					x_o_game_state = gameplay;

					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();

					if (debug.is_debug_mode())
					{
						std::cout << "\n Play Game Selected! \n" << std::endl;
					}

				}


				else if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_B && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ( (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN ) ) )
				{
					//revert all texture and  go to menu
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					game_object_map["Start Game"]->RevertAlteredTextureColor();

					x_o_highlighted_option = none_of_the_options_highlighted;

					if (debug.is_debug_mode())
					{
						std::cout << "\n options_option_highlighted - Exit condition 1 met \n" << std::endl;
					}

				}
				

				break;

			case  options_option_highlighted:
				//left command or click in hit box
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) || (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED ) || (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_LEFT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN))
				{
					x_o_highlighted_option = play_option_highlighted;
					// unhighlight options
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					// highlight play
					game_object_map["Play Button"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "\n Play Button Highlighted \n" << std::endl;
					}

				}


				//right command or click in hit box
				else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK || (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED ) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RIGHT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
				{
					x_o_highlighted_option = credits_option_highlighted;
					// unhighlight options
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					// highlight credits
					game_object_map["Credits Button"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "\n Credits Button Highlighted \n" << std::endl;
					}
				}
				
				else if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_B && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED ) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN ) ) )
				{
					//revert all texture and  go to menu
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					game_object_map["Start Game"]->RevertAlteredTextureColor();

					x_o_highlighted_option = none_of_the_options_highlighted;

					if (debug.is_debug_mode())
					{
						std::cout << "\n play_option_highlighted - Exit condition 1 met \n" << std::endl;
					}
					
				}
				else
				{

				}
				break;

			case  credits_option_highlighted:
				//left command or click in hit box
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) || (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED ) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_LEFT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
				{
					x_o_highlighted_option = options_option_highlighted;
					// unhighlight credits
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					// highlight options
					game_object_map["Options Button"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "\n Options Button Highlighted \n" << std::endl;
					}
				}
				
				else if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_B && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED ) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN ) ) )
				{
					//revert all texture and  go to menu
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					game_object_map["Start Game"]->RevertAlteredTextureColor();

					x_o_highlighted_option = none_of_the_options_highlighted;

					if (debug.is_debug_mode())
					{
						std::cout << "\n credits_option_highlighted - Exit condition 1 met \n" << std::endl;
					}

				}
				
				break;

			case  none_of_the_options_highlighted:

				// highight play if button is not keyboard escape or button B

				if((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_B) && (csdl_obj->GetSDLGameEvent()->type == SDL_CONTROLLERBUTTONDOWN))
				{
					//revert all texture and  go to menu
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					game_object_map["Start Game"]->RevertAlteredTextureColor();

					x_o_game_state = main_menu;

					if (debug.is_debug_mode())
					{
						std::cout << "\n none_of_the_options_highlighted - Controller - Exit condition 2 met \n" << std::endl;
					}

				}				
				else if ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN))
				{
					//revert all texture and  go to menu
					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();
					game_object_map["Start Game"]->RevertAlteredTextureColor();

					x_o_game_state = main_menu;

					if (debug.is_debug_mode())
					{
						std::cout << "\n none_of_the_options_highlighted - Keyboard - Exit condition 2 met \n" << std::endl;
					}
				}
				else 
				{
					//got back one menu

					//opening menu

					game_object_map["Play Button"]->AlterTextureColor(38, 64, 139);


					x_o_highlighted_option = play_option_highlighted;

					if (debug.is_debug_mode())
					{
						std::cout << "\n Play Button Highlighted \n" << std::endl;
					}
					
					

				}

				break;

			default:

				break;
			}

			

		} // end of game_options events

	

	/*
	SDL2 Button input Feedback 

	- not needed for release
	*/

	
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
} //end of Xs an Os game events