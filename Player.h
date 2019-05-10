#include <iostream>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H
class Player{
std::string player_mark;
public:

Player();
~Player();

//optional use by player maybe needed by ai
std::string GetPlayerInput(bool* quit);
void SetPlayerMark(std::string passed_string_mark){player_mark = passed_string_mark;}
std::string GetPlayerMark(){ return player_mark;}
};
#endif //PLAYER_H
