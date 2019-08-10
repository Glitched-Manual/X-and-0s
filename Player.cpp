#include "Player.h"

Player::Player()
{
player_mark = new std::string;
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


//sdl input based on key presses
std::getline(std::cin,player_string_input);
std::cin.ignore(1000,'\n');
std::cin.clear();

if(player_string_input =="quit")
{
 *quit_case = true;
}

return player_string_input;
}
