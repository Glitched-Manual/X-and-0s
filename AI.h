#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "Player.h"
#include "Grid.h"
#include "Developer.h"


#ifndef AI_H
#define AI_H
struct Developer;
class Player;
class Grid;
class Position;
class Tile;


class AI:public Player
{
	std::string* ai_mark;
	std::string* player_input_string;
	bool available_tile_positions_collected = false;
	Grid* game_grid;
	enum PlayerType { computer_player };
	PlayerType current_player_type = computer_player;
	/*
	vector to contain the available positions for ai

	- empty vector in destructor or game result
	*/
	std::vector<Position*> available_tile_positions;

	

public:

	
	AI(std::string* passed_input_string, Grid* passed_grid);
	AI(const AI& obj, Grid* passed_grid);
	~AI();
	 //if ai is active in human vs ai Import grid
	void ImportGrid( Grid* passed_grid) { game_grid = passed_grid; }
	 std::string GetPlayerInput(bool* quit); //not needed can use the ai will not be able to quit //use but do ai stuff
	 void SetPlayerMark(std::string passed_string_mark);
	 std::string* GetPlayerMark() { return ai_mark; }
	 void ResetAIPlayerValues();

	 void CollectAvailablePositions();
	 void SetToAIMode() { current_player_type = computer_player; }
	 int RandomAIMove();
	 void DisplayAvailablePositionsVector();
	
};

#endif //AI_H
