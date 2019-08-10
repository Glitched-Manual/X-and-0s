#include "AI.h"
//do this last

AI::AI()
{
	ai_mark = new std::string;
}
AI::AI(const AI& obj)
{
	ai_mark = new std::string;
}
AI::~AI()
{
	
}

std::string AI::GetPlayerInput(bool* quit)
{
		

	//check for available Positions

	//select one available

	int random_index_select = RandomAIMove();
	//convert selected to string or create new way to select

	std::string ai_x_position_input = std::to_string( (*available_tile_positions[random_index_select]->GetX() + '0') );
	std::string ai_y_position_input = std::to_string((*available_tile_positions[random_index_select]->GetY()) + '0');
	std::string ai_player_move_input_string = ai_x_position_input + 'x' + ai_y_position_input;
	
	return "0x0";
}

int AI::RandomAIMove() 
{
	srand(time(0));

	unsigned short int random_move_index_selector; 

	unsigned short int random_move_index_max_value =  available_tile_positions.size();

	unsigned short int random_move_random_number = rand() % random_move_index_max_value;

	return random_move_random_number;

}


void AI::SetPlayerMark(std::string passed_string_mark)
{
	*ai_mark = passed_string_mark;
}

void AI::CollectAvailablePositions()
{
	//call collect available Tiles once before the AIs first turn
	//find available
	for (unsigned int x_pos = 0; x_pos < 3; x_pos++)
	{
		for (unsigned int y_pos = 0; y_pos < 3; y_pos++)
		{
			
			if (game_grid->GetGameTile(x_pos, y_pos).GetTileIsMarkedStatus())
			{
				//tile is not available
				if (debug.is_debug_mode())
				{
					std::cout << "The Tile located at " << x_pos << " by " << y_pos << " is unvailable." << std::endl;
				}
				//pop position from available tiles vector
				if (available_tile_positions_collected == true)
				{
					//double check if vector is not set
					if (!(available_tile_positions.empty()))
					{
						for (std::vector<Position*>::iterator available_tile_positions_index = available_tile_positions.begin(); available_tile_positions_index != available_tile_positions.end(); available_tile_positions_index++)
						{
							//erase the vector with the position of the marked tile
							if ((*(*available_tile_positions_index)->GetX() == x_pos) && (*(*available_tile_positions_index)->GetY() == y_pos))
							{
								available_tile_positions.erase(available_tile_positions_index);
							}

						}
					}

				}
			}
			else
			{

				//if available tiles are not set, push postions to available tiles vector
				if (available_tile_positions_collected == false)
				{
					available_tile_positions.push_back(new Position(x_pos, y_pos));
				}
			}

		}
	}
	if (available_tile_positions_collected == false)
	{
		available_tile_positions_collected = true;
	}
	if (debug.is_debug_mode())
	{
		std::cout << "AI has completed checking for available Positions" << std::endl;
	}

}