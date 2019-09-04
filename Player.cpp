#include "Player.h"

Player::Player()
{
	player_type = "Human";

   player_mark = new std::string;
}

Player::Player(const Player& obj)
{
	player_mark = new std::string;

	player_type = "?";
	
	if (debug.is_debug_mode())
	{
		std::cout << "Player::Player(const Player& obj) called player type " << std::endl;
	}
}

Player::Player(std::string* passed_input_string,CSDL* passed_csdl_obj)
{

	player_type = "Human";
	player_mark = new std::string; // lol forgot to put this here :P

	sdl_player_input_string = passed_input_string;

	csdl_obj = passed_csdl_obj;
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


if(player_string_input =="quit")
{
 *quit_case = true;
}


return player_string_input;
}
