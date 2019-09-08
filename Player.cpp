#include "Player.h"

Player::Player()
{
	player_type = "Human";

	player_mark = new std::string;

	match_mark_position = new Position;
	LoadSelectorDirections();
}

Player::Player(const Player& obj)
{
	player_mark = new std::string;

	player_type = "?";

	match_mark_position = new Position;

	if (debug.is_debug_mode())
	{
		std::cout << "Player::Player(const Player& obj) called player type " << std::endl;
	}

}

Player::Player(std::string* passed_input_string, CSDL* passed_csdl_obj)
{
	match_mark_position = new Position;
	player_type = "Human";
	player_mark = new std::string; // lol forgot to put this here :P

	sdl_player_input_string = passed_input_string;

	csdl_obj = passed_csdl_obj;
	LoadSelectorDirections();
}


Player::~Player()
{

}

void Player::SetPlayerMark(std::string passed_string_mark)
{
	*player_mark = passed_string_mark;
}
//would return string like "2x2"
std::string Player::GetPlayerInput(bool* quit_case)
{

	std::string player_string_input;



	if ((sdl_player_input_string != NULL) && (csdl_obj != NULL))
	{
		//if spacebar pressed  SDLK_SPACE csdl_obj->GetSDLGameEvent()->key.keysym.sym
		if ((csdl_obj->GetSDLGameEvent()->key.keysym.sym == SDLK_SPACE) && (csdl_obj->GetSDLGameEvent()->type == SDL_KEYDOWN))
		{
			player_string_input = *sdl_player_input_string;
		}

		*sdl_player_input_string = ""; // clears input only call here to ensure it is not NULL

	}

	//sdl input based on key presses
	/*std::getline(std::cin,player_string_input);
	std::cin.ignore(1000,'\n');
	std::cin.clear();
	*/

	/* create a character array from sdl inputs return array if enter pressed - only 4 testing

	final input

	mouse click

	button presses

	enter when tile targeted
	*/


	if (player_string_input == "quit")
	{
		*quit_case = true;
	}


	return player_string_input;
}

void Player::LoadSelectorDirections()
{
	selector_direction_map["UP"] = UP;
	selector_direction_map["DOWN"] = DOWN;
	selector_direction_map["LEFT"] = LEFT;
	selector_direction_map["RIGHT"] = RIGHT;

}

void Player::MoveMatchSelector(std::string passed_string_direction)
{

	switch (selector_direction_map[passed_string_direction])
	{

	case UP:
		if (*match_mark_position->GetY() <= 0)
		{
			match_mark_position->SetY(2);
		}
		else
		{

			match_mark_position->SetY((*match_mark_position->GetY() - 1));
		}
		break;

	case DOWN:

		if (*match_mark_position->GetY() >= 2)
		{
			match_mark_position->SetY(0);
		}
		else
		{
			match_mark_position->SetY((*match_mark_position->GetY() + 1));
		}

		break;

	case LEFT:

		if (*match_mark_position->GetX() <= 0)
		{
			match_mark_position->SetY(2);
		}
		else
		{

			match_mark_position->SetX((*match_mark_position->GetY() - 1));
		}

		break;

	case RIGHT:

		if (*match_mark_position->GetX() >= 2)
		{
			match_mark_position->SetY(0);
		}
		else
		{

			match_mark_position->SetY((*match_mark_position->GetX() + 1));
		}

		break;
	default:
		break;

	}

}