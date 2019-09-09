#include "AI.h"
//do this last

AI::AI(const AI& obj, Grid* passed_grid)
{
	srand(time(0));
	ai_mark = new std::string;
	ImportGrid(passed_grid); //forgot to do this lol
	player_input_string = new std::string;
	if (debug.is_debug_mode())
	{
		std::cout << "AI::AI(const AI& obj, Grid* passed_grid) constructor called" << std::endl;
	}
}

AI::AI(std::string* passed_input_string, Grid* passed_grid)
{
	
	player_input_string = passed_input_string;
	srand(time(0));
	ai_mark = new std::string;
	ImportGrid(passed_grid); //forgot to do this lol

	if (debug.is_debug_mode())
	{
		std::cout << "AI::AI(std::string* passed_input_string, Grid* passed_grid) constructor called" << std::endl;
	}
}
AI::~AI()
{
	if (debug.is_debug_mode())
	{
		std::cout << "AI::~AI Destructor called" << std::endl;
	}

	//ai_mark = nullptr;
}

std::string AI::GetPlayerInput(bool* quit)
{


	//check for available Positions

	/*
	checks availble tiles selects a random on from the available_tile_positions vector

	*/
	CollectAvailablePositions();


	int random_index_select = 0;

	//select one available

	if (!available_tile_positions.empty())
	{
		

		random_index_select = RandomAIMove();
	}
	//convert selected to string or create new way to select


	// char(num) + '0'  to get number character
	if (!available_tile_positions.empty())
	{
		if (random_index_select >= available_tile_positions.size())
		{
			random_index_select = available_tile_positions.size() - 1;
		}
		if (debug.is_debug_mode())
		{
			std::cout << "random_index_select = " << random_index_select << std::endl;
		}

		/*
		std::string ai_x_position_input = std::to_string(static_cast<char>( (*available_tile_positions[random_index_select]->GetX() + int('0') ) ) );
		std::string ai_y_position_input = std::to_string(static_cast<char>( (*available_tile_positions[random_index_select]->GetY() + int('0') ) ) );
		*/
		if (debug.is_debug_mode())
		{
			std::cout << "The Tile located at vector " << random_index_select << " was seleceted by the AI." << std::endl;
			std::cout << "The vector has " << available_tile_positions.size() << " available values" << std::endl;
		}
		std::string ai_x_position_input = std::to_string(*available_tile_positions[random_index_select]->GetX() );
		std::string ai_y_position_input = std::to_string( *available_tile_positions[random_index_select]->GetY() );
		std::string ai_player_move_input_string = ai_x_position_input + 'x' + ai_y_position_input;
		//*player_input_string = ai_player_move_input_string;

		
		DisplayAvailablePositionsVector();
		return ai_player_move_input_string;
	}
	*quit = true; //ai fail
	return "0x0";
}

int AI::RandomAIMove()
{
	if (debug.is_debug_mode())
	{
		std::cout << "Generating random numbber..." << std::endl;
	}

	//unsigned short int random_move_index_selector; 

	unsigned short int random_move_index_max_value = available_tile_positions.size();

	unsigned short int random_move_random_number = rand() % random_move_index_max_value;

	if (debug.is_debug_mode())
	{
		std::cout << "Random numbber "<< random_move_random_number <<" was generated!" << std::endl;
	}

	return random_move_random_number;

}


void AI::SetPlayerMark(std::string passed_string_mark)
{
	*ai_mark = passed_string_mark;
}

void AI::CollectAvailablePositions()
{

	std::string remaining_positions_string;
	//call collect available Tiles once before the AIs first turn
	//find available
	for (unsigned int x_pos = 0; x_pos < 3; x_pos++)
	{
		for (unsigned int y_pos = 0; y_pos < 3; y_pos++)
		{
			

				if (game_grid->GetGameTilePtr(x_pos, y_pos)->ReturnTileIsMarkedStatus())
				{
					//tile is not available
					if (debug.is_debug_mode())
					{
						std::cout << "The Tile located at " << x_pos << " by " << y_pos << " is unvailable." << std::endl;
					}
					//pop position from available tiles vector
					if (available_tile_positions_collected == true)
					{
						unsigned int erase_at_index = 0;
						//double check if vector is not set
						if (!(available_tile_positions.empty()))
						{
							for (std::vector<Position*>::iterator available_tile_positions_index = available_tile_positions.begin(); available_tile_positions_index != available_tile_positions.end(); available_tile_positions_index++)
							{
								//erase the vector with the position of the marked tile
								if ((*(*available_tile_positions_index)->GetX() == x_pos) && (*(*available_tile_positions_index)->GetY() == y_pos))
								{
									//available_tile_positions.erase(available_tile_positions.begin() + erase_at_index); crashes code
									//  std::replace_copy (myints, myints+8, myvector.begin(), 20, 99);

									/*
									
									replace with value at back, pop back
									*/
									delete available_tile_positions[available_tile_positions.size() - 1];

									*available_tile_positions_index = available_tile_positions.back();
									
									available_tile_positions.pop_back(); // changes loop and checks deleted addresses by chance

									if (debug.is_debug_mode())
									{
										std::cout << "The Position located in available_tile_positions at [" << erase_at_index << "]  was swtiched back and popped"<< std::endl;
									}
									CollectAvailablePositions();//recursive call may work may fail
								}
								erase_at_index++;
							}
						}

					}
				}
				else //tile is unmarked
				{
										
					//if available tiles are not set, push postions to available tiles vector
					if (available_tile_positions_collected == false)
					{
						if (debug.is_debug_mode())
						{
							std::cout << "AI has added to available Positions" << std::endl;
						}
						available_tile_positions.push_back(new Position(x_pos, y_pos));
						
					}

					
				}
			
			

		}
	}
	if (available_tile_positions_collected == false)
	{
		
			available_tile_positions_collected = true;

			if (debug.is_debug_mode())
			{
				std::cout << "AI has completed checking for available Positions" << std::endl;
			}
				
	}
	

	available_tile_positions_collected = true;
	
}

void AI::ResetAIPlayerValues()
{

	/*
	  if available_tile_positions is not empty

	  pop until empty or use .clear()
	*/
	if (!available_tile_positions.empty())
	{
		available_tile_positions.clear();
	}
	//set available_tile_positions_collected to false
	available_tile_positions_collected = false;

}

void AI::DisplayAvailablePositionsVector()
{
	unsigned int available_position_index_counter = 0;
	//double check if vector is not set
	if (!(available_tile_positions.empty()))
	{
		for (std::vector<Position*>::iterator available_tile_positions_index = available_tile_positions.begin(); available_tile_positions_index != available_tile_positions.end(); available_tile_positions_index++)
		{
			//erase the vector with the position of the marked tile
			
				

				if (debug.is_debug_mode())
				{
					std::cout << "The Position located in available_tile_positions at [" << available_position_index_counter << "]  is available" << std::endl;
					std::cout << "The value is "<< *available_tile_positions.at(available_position_index_counter)->GetX() <<" ,"<< *available_tile_positions.at(available_position_index_counter)->GetY() << std::endl;
				}
			
				available_position_index_counter++;
		}

		available_tile_positions_collected = true;
	}

}