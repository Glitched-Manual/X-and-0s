#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}
//would return string like "2x2"
std::string Player::GetPlayerInput(bool* quit_case)
{

std::string player_string_input;

std::getline(std::cin,player_string_input);
std::cin.ignore(1000,'\n');
std::cin.clear();

if(player_string_input =="quit")
{
 *quit_case = true;
}

return player_string_input;
}
