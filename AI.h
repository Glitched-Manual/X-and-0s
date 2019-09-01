#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Grid.h"
#include "Developer.h"


#ifndef AI_H
#define AI_H
class Player;
class Grid;
class Position;
class Tile;
struct Developer;

class AI:public Player
{
	std::string* ai_mark;
	bool available_tile_positions_collected = false;
	Grid* game_grid;

	/*
	vector to contain the available positions for ai

	- empty vector in destructor or game result
	*/
	std::vector<Position*> available_tile_positions;

	Developer debug; // create as pointer later so there is only one Developer obj

public:

	AI();
	AI(const AI& obj);
	~AI();
	 //if ai is active in human vs ai Import grid
	void ImportGrid( Grid* passed_grid) { game_grid = passed_grid; }
	 std::string GetPlayerInput(bool* quit); //not needed can use the ai will not be able to quit //use but do ai stuff
	 void SetPlayerMark(std::string passed_string_mark);
	 std::string* GetPlayerMark() { return ai_mark; }
	 void ResetAIPlayerValues();

	 void CollectAvailablePositions();

	 int RandomAIMove();
};

#endif //AI_H
