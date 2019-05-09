#include <iostream>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H
class Player{

public:

Player();
~Player();

//optional use by player maybe needed by ai
std::string GetPlayerInput(bool* quit);
};
#endif //PLAYER_H
