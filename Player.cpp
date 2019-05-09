#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}
//would return string like "2x2"
std::string Player::GetPlayerInput()
{

std::string player_string_input;

std::getline(std::cin,player_string_input);
std::cin.ignore(1000,'\n');
std::cin.clear();

return player_string_input;
}
