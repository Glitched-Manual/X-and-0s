#include <iostream>
#include <string>
#include <map> 

#include "Developer.h"
#include "CSDL.h"
#include "Position.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
std::string* player_mark;
std::string player_type;
std::string* sdl_player_input_string = NULL;
enum PlayerType {human_player,computer_player};

PlayerType current_player_type;

enum MatchSelectorDirections { UP, DOWN, LEFT, RIGHT };

std::map<std::string, MatchSelectorDirections> selector_direction_map;

CSDL* csdl_obj = NULL;


Position* match_mark_position;
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

void LoadSelectorDirections();

void MoveMatchSelector(std::string passed_string_direction);
};
#endif //PLAYER_H
