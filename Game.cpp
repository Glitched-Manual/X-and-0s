#include "Game.h"

Game::Game(unsigned int passed_screen_width, unsigned int passed_screen_height)
{

	SCREEN_WIDTH = passed_screen_width;
	SCREEN_HEIGHT = passed_screen_height;
	sdl_player_input_string = new std::string;

	total_turns = 0;

	game_grid = new Grid; //add params
	csdl_obj = new CSDL(SCREEN_WIDTH, SCREEN_HEIGHT);

	player_pos_1 = new Player(sdl_player_input_string, csdl_obj); //lol fully redeclared before going out out scope or passing value into args cause segmentation errors
	
	/*

	if Player vs computer change Player2 to AI
	
	*/

	if (x_o_gameplay_mode == human_vs_computer)
	{
		//delete player_pos_2;
	   //player_pos_2 = nullptr;
		AI* game_bot7000 = new AI(sdl_player_input_string,game_grid);
		player_pos_2 = game_bot7000;
		player_pos_2->SetPlayerMark("#");
	}
	else 
	{
		player_pos_2 = new Player(sdl_player_input_string, csdl_obj); //if ai use diffent initailizer 
		player_pos_2->SetPlayerMark("#");
	}
	
	Game_Over = false;
	quit_game_from_input = false;
	win_cases_loaded = false;

	player_pos_1->SetPlayerMark("!");
	player_pos_2->SetPlayerMark("#");
	LoadWinCases();

	if (debug.is_debug_mode())
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

	//load opponent options

	LoadOpponentOptions(); // forgot to uncomment on finishing lol

	loadPlayerTextureMarks(); // test version load two marks

	LoadPlayAgainPrompt(); // test version loads rematch prompt



	LoadTileSelector();//loads cursor selector


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
	//use quit_game_from_inputto quit game 
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
		UpdateGameTextures();

		//clean

		SDL_RenderPresent(csdl_obj->GetSDLRenderer());
	}

}

void Game::SetupSecondPlayerValue()
{

	if (x_o_gameplay_mode == human_vs_computer)
	{
	//	delete player_pos_2;
	//	player_pos_2 = nullptr;
		AI* game_bot7000 = new AI(sdl_player_input_string, game_grid);
		player_pos_2 = game_bot7000;
		player_pos_2->SetPlayerMark("#");
	}
	else
	{
		player_pos_2 = new Player(sdl_player_input_string, csdl_obj); //if ai use diffent initailizer 
		player_pos_2->SetPlayerMark("#");
	}
	SetCurrentPlayerTurn();
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
	if (quit_game_from_input)
	{
		delete position_to_mark_obj;
		return 0;
	}
	else if (p1ayer_input == "")//remove this
	{
		std::cout << "No input found. Please enter a position example \"1x1\"" << std::endl;
		delete position_to_mark_obj;
		return 4;
	}
	if (FilterUserInput(p1ayer_input, position_to_mark_obj))
	{
		//check if player can mark square
		if (CheckIfTileIsAvailable(position_to_mark_obj))
		{
			std::cout << "check if available" << std::endl;
			//mark square if available
			SetGameTileMark(position_to_mark_obj, *current_player->GetPlayerMark());//triggers segmentation error
			std::cout << "Tile marked" << std::endl;
			total_turns++; //caused endless loop other comment stuck on other players turn
		}
	}
	delete position_to_mark_obj;
	return 1;
}

//lol forgot to change the type from bool to void
//add player_obj to get players mark
void Game::SetGameTileMark(Position* position_to_mark, std::string player_mark)
{

	GetGameGrid()->GetGameTile(*position_to_mark->GetX(), *position_to_mark->GetY()).SetTileMark(player_mark);

	//current_player.GetPlayerMark(); causes segmentation error
}

bool Game::CheckIfTileIsAvailable(Position* passed_position_to_check)
{
	std::cout << "Game::CheckIfTileIsAvailable  get position" << std::endl;
	if ((*GetGameGrid()->GetGameTile(*passed_position_to_check->GetX(), *passed_position_to_check->GetY()).GetTileIsMarkedStatus()) == true)
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

bool Game::FilterUserInput(std::string raw_input_string, Position* passed_position)
{

	int x_pos = 0;
	int y_pos = 0;
	unsigned int mode = 0;
	bool filter_successful = false;
	enum axis { x_cord, y_cord };

	if (debug.is_debug_mode())
	{
		std::cout << "filtering " << raw_input_string << std::endl;
	}

	for (unsigned int ind = 0; ind < raw_input_string.length(); ind++)
	{
		if ((raw_input_string[ind] == 'x') | (raw_input_string[ind] == 'X'))
		{
			mode = y_cord;
		}
		if (isdigit(raw_input_string[ind])) {

			if (mode == x_cord)
			{
				x_pos = (x_pos * 10) + (char(raw_input_string[ind]) - 48);
			}
			else
			{
				y_pos = (y_pos * 10) + (char(raw_input_string[ind]) - 48);
				if (!filter_successful)
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

	if ((mode == y_cord) && (filter_successful))
	{

		if ((x_pos < 3) & (y_pos < 3))
		{
			passed_position->SetX(x_pos);
			passed_position->SetY(y_pos);
		}
		else
		{
			if (debug.is_debug_mode())
			{
				std::cout << "Game.cpp FilterUserInput error: (  "<<x_pos <<" < 3)&( "<< y_pos<< " < 3) found false" << std::endl;
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

	win_cases[x].SetWinCaseCombination(Position(0, 0), Position(1, 0), Position(2, 0));
	++x;
	win_cases[x].SetWinCaseCombination(Position(0, 1), Position(1, 1), Position(2, 1));
	++x;
	win_cases[x].SetWinCaseCombination(Position(0, 2), Position(1, 2), Position(2, 2));
	++x;
	win_cases[x].SetWinCaseCombination(Position(0, 0), Position(0, 1), Position(0, 2));
	++x;
	win_cases[x].SetWinCaseCombination(Position(1, 0), Position(1, 1), Position(1, 2));
	++x;
	win_cases[x].SetWinCaseCombination(Position(2, 0), Position(2, 1), Position(2, 2));
	++x;
	win_cases[x].SetWinCaseCombination(Position(0, 0), Position(1, 1), Position(2, 2));
	++x;
	win_cases[x].SetWinCaseCombination(Position(2, 0), Position(1, 1), Position(0, 2));

	if (debug.is_debug_mode())
	{
		std::cout << "LoadWinCase End" << std::endl;

		std::cout << *win_cases[0].GetCombination(1)->GetX() << " , " << *win_cases[0].GetCombination(1)->GetY() << std::endl;
	}

	win_cases_loaded = true;

}

Win_Case Game::GetWinCase(int passed_win_case_index)
{

	if (passed_win_case_index > 7)
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


	for (int wincase_index = 0; wincase_index < 8; wincase_index++)
	{
		int mark_true_case = 0;

		for (int wincase_combination_index = 0; wincase_combination_index < 3; wincase_combination_index++)
		{
			if (*passed_player->GetPlayerMark() == *GetGameGrid()->GetGameTile(*GetWinCase(wincase_index).GetCombination(wincase_combination_index)->GetX(), *GetWinCase(wincase_index).GetCombination(wincase_combination_index)->GetY()).GetTileMark())
			{
				++mark_true_case;
				if (debug.is_debug_mode())
				{
					std::cout << "Marked case = " << mark_true_case << std::endl;
				}

			}

		}
		// check if three matches were found
		if (mark_true_case == 3)
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


//fix after events and graphics

//call on click of keyboard, button, mouse input conditions met

void Game::SetCurrentPlayerTurn()
{
	if (total_turns % 2 == 0)
	{
		if(players_turn_order == 0)
		{
			//p1 turn
			x_o_current_player_turn = Player_1_turn;
		}
		else
		{
			//p2 turn
			x_o_current_player_turn = Player_2_turn;
		}
	}
	else
	{
		if (players_turn_order == 0)
		{
			//p2 turn
			x_o_current_player_turn = Player_2_turn;
		}
		else
		{
			//p1 turn
			x_o_current_player_turn = Player_1_turn;
		}
	}

}


void Game::TurnPhaseEvent()
{

	if ((!Game_Over) && !(total_turns > 8))
	{
		
		if (total_turns % 2 == players_turn_order) //make false to change turn order to player_pos_2 starting if 0 p1 first. 1 p2 first
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
				Game_Over = true; // add play again case
				current_game_result = player1_wins;
				//draw to screen
			}
		}
		else if (total_turns % 2 == 0)
		{
			// bool check if player2 won
			if (PlayerWin(player_pos_2))
			{
				std::cout << "Player 2 Wins!!" << std::endl;
				Game_Over = true;
				current_game_result = player2_wins;
				//draw to screen
			}
		}
	}
	if ((total_turns > 8) && (Game_Over == false)) {
		//Draw case

		Game_Over = true;
		std::cout << "Draw!" << std::endl;
		current_game_result = match_draw;
		//draw to screen
	}
	SetCurrentPlayerTurn();
}


void Game::GameRematchReset()
{
	/*
	player_pos_1->SetPlayerMark("!");
	player_pos_2->SetPlayerMark("#");
	

	reset tiles
	 - marked bool
	 - tile_mark to anything other than "!" or "#"

	if ai reset

	change game_result to none

	turn Game_Over false



	*/
	//resets tiles
	game_grid->ResetAllTileAttributes();

	//reset AI
	if (x_o_gameplay_mode == human_vs_computer)
	{
		player_pos_2->ResetAIPlayerValues();
	}

	///set total_turns to 0. forgot I lol

	total_turns = 0;
	//Reset Result to none
	current_game_result = no_result;
	
	//GameOver to false

	Game_Over = false;

	if (debug.is_debug_mode())
	{
		std::cout << "\nAll match values were reset!\n" << std::endl;
	}
}

bool Game::LoadGameplayObjects()
{
	GameObject* hash_table_game_obj = NULL;
	//load hash table
	HashTable* hash_table = new HashTable(new LoaderParams(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 400, 400, "Hash Table"));

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
	start_menu_text = new GameText(new LoaderParams(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, "Start Game"), 60);

	if (start_menu_text == NULL)
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


bool Game::LoadOpponentOptions()
{
	/*
	two texts "PVC" and "PVP"
	*/

	GameObject* player_vs_computer_text = NULL;

	//start_menu_text = new GameText(new LoaderParams(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, "Start Game"), 60);

	GameText* player_vs_computer_game_text = new GameText(new LoaderParams((SCREEN_WIDTH / 4), SCREEN_HEIGHT / 2, 100, 100, "Player VS AI"), "Player v Comp", 30);

	player_vs_computer_text = player_vs_computer_game_text;

	game_object_map["Player VS Comp"] = player_vs_computer_text;

	allGameObjects.push_back(player_vs_computer_text);


	//Two player mode

	GameObject* player_vs_player_text = NULL; //map and vector need value of game object type

	//set values of text

	GameText* player_vs_player_game_text = new GameText(new LoaderParams((SCREEN_WIDTH / 4) * 3, SCREEN_HEIGHT / 2, 100, 100, "Player VS Player"), "Player v Player", 30);

	// make GameObject point to GameText object
	player_vs_player_text = player_vs_player_game_text;

	game_object_map["Player VS Player"] = player_vs_player_text;

	allGameObjects.push_back(player_vs_player_text);

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

	GameText* options_menu_credits = new GameText(new LoaderParams((SCREEN_WIDTH / 5) * 4, (SCREEN_HEIGHT / 2), 100, 100, "Credits Button"), "Credits", 30);


	game_options_menu_credits_text = options_menu_credits;

	game_object_map["Credits Button"] = game_options_menu_credits_text;

	allGameObjects.push_back(game_options_menu_credits_text);

	return true;
}

bool Game::loadPlayerTextureMarks()
{

	GameObject* player_tile_mark_gam_obj = NULL; // will need two one for each player

	//need rect* of hash table , make x and y change depending on maked tiles


	TileMarker* tile_marker_obj = new TileMarker(new LoaderParams((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 100, 100, "test mark"), game_grid, player_pos_1, game_object_map["Hash Table"]->GetTextureRect()); // may only the player string mark is needed

	player_tile_mark_gam_obj = tile_marker_obj;
	   
	game_object_map["test mark"] = tile_marker_obj; // did not use game object here

	allGameObjects.push_back(player_tile_mark_gam_obj); //pushed TileMark instead of game object lol

	if (debug.is_debug_mode())
	{
		std::cout << "Player mark loaded" << std::endl;
	}

	return true;
}


bool Game::LoadPlayAgainPrompt()
{
	GameObject* prompt_window_game_object = NULL;
	//create promptWindow
	PromptWindow* rematch_prompt = new PromptWindow(new LoaderParams(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 400, 200, "rematch prompt"),csdl_obj);
	//add more text
	/*
	
	rematch_prompt->CreatePromptText(x percentage of prompt window,y percentage of prompt window,"text id","text message",text size);

	*/
	rematch_prompt->CreatePromptText(50,25,"play again rematch text","Play Again?",20);
	rematch_prompt->CreatePromptText(25, 50, "yes rematch text", "YES", 20);
	rematch_prompt->CreatePromptText(75, 50, "no rematch text", "NO", 20);
	//pin to game object
	prompt_window_game_object = rematch_prompt;
	// add map and vector

	game_object_map["rematch prompt"] = prompt_window_game_object;

	allGameObjects.push_back(prompt_window_game_object);

	return true;
}
//call after loading hash_table
bool Game::LoadTileSelector()
{
	GameObject* game_object_tile_selector = NULL;
	/*
	
	TileSelector(LoaderParams* pParams, Grid* passed_grid, SDL_Rect* passed_hash_table_rect, CSDL* passed_csdl_obj, std::string passed_id_name);
	*/

	//
	TileSelector* tile_selector_buffer = new TileSelector(new LoaderParams(10,10,50,50,"tile_selector cursor"),game_grid, game_object_map["Hash Table"]->GetTextureRect(),csdl_obj,"tile_selector cursor");


	/*
	To call move direction
	*/
	game_tile_selector = tile_selector_buffer;
    //as game object
	game_object_tile_selector = tile_selector_buffer;
    //as part of object map
	game_object_map["tile_selector cursor"] = game_object_tile_selector;

	/*
	change color

	71,91,99 - DEEP SPACE SPARKLE

	117, 201, 200 - MOONSTONE BLUE

	*/
	game_object_map["tile_selector cursor"]->AlterTextureColor(71, 91, 99);
	allGameObjects.push_back(game_object_tile_selector);

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

		else if (x_o_game_state == opponent_selection)
		{
			game_object_map["Player VS Comp"]->Draw(csdl_obj->GetSDLRenderer());

			game_object_map["Player VS Player"]->Draw(csdl_obj->GetSDLRenderer());

		}

		else if (x_o_game_state == match_gameplay)
		{

			//render grid
			game_object_map["Hash Table"]->Draw(csdl_obj->GetSDLRenderer());

			/*
			render hit boxes
			*/

			//loop through marked tiles , render marks to proper spots
			game_object_map["test mark"]->Draw(csdl_obj->GetSDLRenderer());

			//if game over as player if they want to play again
			if(Game_Over)
			{
				game_object_map["rematch prompt"]->Draw(csdl_obj->GetSDLRenderer());
			}

		}

		else //render everything! probably bad :P
		{
			for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
			{
				(*game_object_index)->Draw(csdl_obj->GetSDLRenderer());
			}

		}
		//will always be rendered last here
		game_object_map["tile_selector cursor"]->Draw(csdl_obj->GetSDLRenderer());
	}
}

void Game::UpdateGameTextures()
{

	if (!(allGameObjects.empty()))
	{

		for (std::vector<GameObject*>::iterator game_object_index = allGameObjects.begin(); game_object_index != allGameObjects.end(); game_object_index++)
		{
			/*
			updates game objects perhaps the most taxing method
			maybe update only what is draw
			*/
			(*game_object_index)->Update();
		}
		

	}
	else
	{
		if (debug.is_debug_mode())
		{
			std::cout << "Game::LoadGameObjectContent() Error - allGameObjects found empty!" << std::endl;
		}
		
	}

}

void Game::GameEventManager()
{
	


		//if at main menu
		if (x_o_game_state == main_menu)
		{
			//if keyboard or controller pressed


				//if start button or enter key pressed
			if ((csdl_obj->ButtonInputCheck("START")) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RETURN && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
			{
				if (debug.is_debug_mode())
				{
					std::cout << "\nYou Started the game!\n" << std::endl;
				}
				//rgb(38, 64, 139)
				game_object_map["Start Game"]->AlterTextureColor(38, 64, 139);


				//create a change state to put values back to starting position
				x_o_game_state = game_options;

				RevertGameObjectColorList("Start Game");
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
			else if (total_text_highlighted < 0)
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
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) || (csdl_obj->ButtonInputCheck("RIGHT") && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RIGHT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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


				else if ((csdl_obj->ButtonInputCheck("START")) || (csdl_obj->ButtonInputCheck("A_ACTION")) || (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RETURN))
				{
					x_o_game_state = opponent_selection;

					game_object_map["Play Button"]->RevertAlteredTextureColor();
					game_object_map["Options Button"]->RevertAlteredTextureColor();
					game_object_map["Credits Button"]->RevertAlteredTextureColor();

					if (debug.is_debug_mode())
					{
						std::cout << "\n Play Game Selected! \n" << std::endl;
					}

				}


				else if ((csdl_obj->ButtonInputCheck("B_ACTION") ) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) || (csdl_obj->ButtonInputCheck("LEFT") && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_LEFT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN))
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
				else if (csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK || (csdl_obj->ButtonInputCheck("RIGHT") && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RIGHT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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

				else if ((csdl_obj->ButtonInputCheck("B_ACTION")) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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
				if ((csdl_obj->GetSDLGameEvent()->cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) || (csdl_obj->ButtonInputCheck("LEFT") && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_LEFT) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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

				else if ((csdl_obj->ButtonInputCheck("B_ACTION") && csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED) || ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_ESCAPE && csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)))
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

				if ((csdl_obj->ButtonInputCheck("B_ACTION")))
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
					RevertGameObjectColorList("Play Button", "Options Button", "Credits Button");

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

         // select player v player or player v computer
		else if (x_o_game_state == opponent_selection)
		{
			// Player vs computer or Player vs Player

			//check if both are highlighted unhighlight both if true
			if ((game_object_map["Player VS Comp"]->GetAreColorsAltered() == true) && (game_object_map["Player VS Player"]->GetAreColorsAltered() == true))
			{
				
				RevertGameObjectColorList("Player VS Comp", "Player VS Player");

				if (debug.is_debug_mode())
				{
					std::cout << "Both Texts found highlighted. Then reverted" << std::endl;
				}

			}

			//if no options highlighted
			if ((game_object_map["Player VS Comp"]->GetAreColorsAltered() == false) && (game_object_map["Player VS Player"]->GetAreColorsAltered() == false))
			{
				if ( ( csdl_obj->ButtonInputCheck("B_ACTION") ) || (csdl_obj->ButtonInputCheck("ESCAPE") ) )
				{
					// go back
					
					x_o_game_state = game_options;

					if (debug.is_debug_mode())
					{
						std::cout << "Back Option Selected" << std::endl;
					}
				}
								

				else
				{
					//highlight PVC right - may be a problem later
					game_object_map["Player VS Comp"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "Player VS Comp Highlighted" << std::endl;
					}
				}
			}
			// Player Vs Computer Highlighted
			else if (game_object_map["Player VS Comp"]->GetAreColorsAltered() == true)
			{

				//right press
				if ( csdl_obj->ButtonInputCheck("RIGHT") )
				{
					//AlterTextureColor(38, 64, 139)
					
					//unhighlight P V C

					//game_object_map["Player VS Comp"]->RevertAlteredTextureColor();
					RevertGameObjectColorList("Player VS Comp");

					//highlight P V P text

					game_object_map["Player VS Player"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "" << std::endl;
					}
				}

				//enter or A make shorter some how. just make more else if conditions. Call methods
				else if ((csdl_obj->ButtonInputCheck("START")) || (csdl_obj->ButtonInputCheck("A_ACTION")) || (csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_RETURN))
				{
					x_o_gameplay_mode = human_vs_computer;
					SetupSecondPlayerValue();
					
					//change to gameplay scene

					x_o_game_state = match_gameplay;

					
					//unhighlight all text 
					
					//game_object_map["Player VS Comp"]->RevertAlteredTextureColor();
					//game_object_map["Player VS Player"]->RevertAlteredTextureColor();
					RevertGameObjectColorList("Player VS Comp");

					if (debug.is_debug_mode())
					{
						std::cout << "" << std::endl;
					}

				}

				// esc or B

				else if ( (csdl_obj->ButtonInputCheck("B_ACTION")) || (csdl_obj->ButtonInputCheck("ESCAPE")) )
				{
					RevertGameObjectColorList("Player VS Comp");

					if (debug.is_debug_mode())
					{
						std::cout << "Player VS Comp unhighlighted - exit condition 1" << std::endl;
					}
				}

				
			}

			//Player vs Player highlighted

			else if (game_object_map["Player VS Player"]->GetAreColorsAltered() == true)
			{
				//left press keyboard + controller
				if ( csdl_obj->ButtonInputCheck("LEFT") )
				{
					RevertGameObjectColorList("Player VS Player");
					//highlight PVC
					game_object_map["Player VS Comp"]->AlterTextureColor(38, 64, 139);

					if (debug.is_debug_mode())
					{
						std::cout << "" << std::endl;
					}

				}

				


				//enter or A or start controller
				else if ( (csdl_obj->ButtonInputCheck("A_ACTION")) || (csdl_obj->ButtonInputCheck("START")) )
				{
					//
					
					x_o_gameplay_mode = human_vs_human;
					SetupSecondPlayerValue();
					x_o_game_state = match_gameplay;

					RevertGameObjectColorList("Player VS Player");

					if (debug.is_debug_mode())
					{
						std::cout << "" << std::endl;
					}
				}



				// esc or B

				else if ( csdl_obj->ButtonInputCheck("B_ACTION") || csdl_obj->ButtonInputCheck("ESCAPE"))
				{
					RevertGameObjectColorList("Player VS Player");

					if (debug.is_debug_mode())
					{
						std::cout << "Player VS Player text unhighlighted - Exit condition 1" << std::endl;
					}
				}
			}

			//

		}


		else if (x_o_game_state == match_gameplay)
		{
		//if paused or rematch prompt
		if (menu_activated) 
		{

		}
		else if (Game_Over)
		{
			//do something with rematch prompt

			/*
			rematch_prompt->CreatePromptText(25, 50, "yes rematch text", "YES", 20);
	rematch_prompt->CreatePromptText(75, 50, "no rematch text", "NO", 20);
			*/
			//both options highlighted
			if(game_object_map["rematch prompt"]->GetAreColorsAltered("yes rematch text")&&(game_object_map["rematch prompt"]->GetAreColorsAltered("no rematch text")))
			{
				game_object_map["rematch prompt"]->RevertAlteredTextureColor("yes rematch text");
				game_object_map["rematch prompt"]->RevertAlteredTextureColor("no rematch text");
			}

			//YES highlighted
			else if (game_object_map["rematch prompt"]->GetAreColorsAltered("yes rematch text"))
			{
				//Left or Right pressed
				if (csdl_obj->ButtonInputCheck("LEFT")|| csdl_obj->ButtonInputCheck("RIGHT"))
				{
					game_object_map["rematch prompt"]->RevertAlteredTextureColor("yes rematch text");
					game_object_map["rematch prompt"]->AlterTextureColor("no rematch text", 38, 64, 139);

					//if A or Start Pressed
				}
				//if A or Start Pressed
				else if (csdl_obj->ButtonInputCheck("A_ACTION") || csdl_obj->ButtonInputCheck("START"))
				{

					//reset 
					GameRematchReset();

				}
			}
			//NO Highlighted
			else if (game_object_map["rematch prompt"]->GetAreColorsAltered("no rematch text"))
			{
				//Left or Right pressed
				if (csdl_obj->ButtonInputCheck("LEFT") || csdl_obj->ButtonInputCheck("RIGHT"))
				{
					game_object_map["rematch prompt"]->RevertAlteredTextureColor("no rematch text");
					game_object_map["rematch prompt"]->AlterTextureColor("yes rematch text", 38, 64, 139);

				}

				//if A or Start Pressed
				else if (csdl_obj->ButtonInputCheck("A_ACTION") || csdl_obj->ButtonInputCheck("START"))
				{
					//reset  
					GameRematchReset();
					
					//return to options menu

					x_o_game_state = game_options;
				}
			}
			//none highlighted
			else
			{
				//any button highlight YES
				if (csdl_obj->GetSDLGameEvent()->cbutton.state == SDL_PRESSED)
				{
					game_object_map["rematch prompt"]->AlterTextureColor("yes rematch text", 38, 64, 139);
				}
				if (csdl_obj->GetSDLGameEvent()->key.state == SDL_PRESSED)
				{
					game_object_map["rematch prompt"]->AlterTextureColor("yes rematch text", 38, 64, 139);
				}
			}

		}
		else
		{
			if (csdl_obj->ButtonInputCheck("SPACE"))
			{
				/*
				call turn phase method

				if the string value of sdl_player_input_string is valid and the selected tile is available the tile should get marked

				clear if invalid or valid
				*/
				TurnPhaseEvent();
			}

			/*
			if A ,Enter , or click occurs on a tile it is marked if available

			collision returns a position value to check
			*/


		}

			

		} //end of match_gameplay events

		/*
		SDL2 Button input Feedback

		- not needed for release
		*/



		if (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN)
		{

			unsigned int sdl_keyboard_input = csdl_obj->GetSDLGameEvent()->key.keysym.sym;

			std::cout << csdl_obj->GetSDLGameEvent()->key.keysym.sym << std::endl;



			if (((sdl_keyboard_input > 47) && (sdl_keyboard_input < 58)) || ((sdl_keyboard_input > 96) && (sdl_keyboard_input < 123)))
			{
				printf("\nWhich is also equal to : %c \n", sdl_keyboard_input);
				*sdl_player_input_string += char(sdl_keyboard_input);
				std::cout << "Player input string = " << *sdl_player_input_string << std::endl;
				if (sdl_player_input_string->length() >= 5)
				{
					*sdl_player_input_string = "";

					std::cout << "Player input string too long" << std::endl;
				}
			}
		}

		if (csdl_obj->GetSDLGameEvent()->type == SDL_CONTROLLERBUTTONDOWN)
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

	
} //end of Xs an Os game events



void Game::RevertGameObjectColorList()
{
	
}

//To change highlighted text back to white, or as defined in class
template<typename... String_args>
void Game::RevertGameObjectColorList(std::string passed_string_arg, String_args... other_passed_string_args)
{
	// if an incorrect string is entered problems will happen
	game_object_map[passed_string_arg]->RevertAlteredTextureColor();

	RevertGameObjectColorList(other_passed_string_args...);
}

template<typename... Basic_string_args>
void Game::RevertGameObjectColorList(char* passed_string_arg, Basic_string_args... other_passed_string_args)
{
	std::string converted_string_arg = std::to_string(passed_string_arg);
	// if an incorrect string is entered problems will happen
	game_object_map[converted_string_arg]->RevertAlteredTextureColor();

	RevertGameObjectColorList(other_passed_string_args...);
}
