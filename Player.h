#include <iostream>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H
class Player{
std::string* player_mark;
public:

Player();
~Player();


virtual std::string GetPlayerInput(bool* quit);
virtual void SetPlayerMark(std::string passed_string_mark);
virtual std::string* GetPlayerMark(){ return player_mark;}
};
#endif //PLAYER_H
