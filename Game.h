#include "Grid.h"
#include "Win_Case.h"
#include "Player.h"
#include "AI.h"
#include <memory>

#ifndef GAME_H
#define GAME_H

class Win_case;
class Grid;
class Player;
class AI;
class Position;
class Game{
//Player* pos_1
Player* player_pos_1;
//Player pos_2;
Player* player_pos_2;
unsigned int total_turns;
bool Game_Over;
bool quit;
Grid* game_grid;

Win_Case win_cases[8];
unsigned int turn_phase;
public:
Game();
~Game();
//filter check then mark
bool FilterUserInput(std::string raw_input_string,Position& passed_position);
bool CheckIfTileIsAvailable(Position passed_position_to_check);
Grid* GetGameGrid(){ return game_grid;}
int GetTurnPhase(){ return turn_phase; }
bool PlayerWin();

void LoadWinCases();

void GameLoop();
void SetTileMark(Position position_to_mark,std::string player_mark);
int PlayerTurn(Player* current_player);
};
#endif //GAME_H
