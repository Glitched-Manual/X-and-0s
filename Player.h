#include <iostream>
#include <string>

#include "Developer.h"
#include "CSDL.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
std::string* player_mark;
std::string player_type;
std::string* sdl_player_input_string = NULL;
enum PlayerType {human_player,computer_player};
PlayerType current_player_type;
CSDL* csdl_obj = NULL;

Developer debug;
public:

Player();
Player(std::string* passed_input_string, CSDL* passed_csdl_obj);
Player(const Player& obj);
~Player();


virtual std::string GetPlayerInput(bool* quit);
virtual std::string GetPlayerType() {	return player_type; }
virtual void SetPlayerMark(std::string passed_string_mark);
virtual std::string* GetPlayerMark(){ return player_mark;}
virtual void SetToAIMode() { current_player_type = computer_player; }
virtual void ResetAIPlayerValues(){}
};
#endif //PLAYER_H
