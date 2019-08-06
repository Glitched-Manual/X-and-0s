#include "Grid.h"
#include "Win_Case.h"
#include "Player.h"
#include "AI.h"
#include <memory>
#include <vector>
#include "CSDL.h"
#include "HashTable.h"

#ifndef GAME_H
#define GAME_H
struct Developer;
class Win_case;
class Grid;
class Player;
class AI;
class Position;
class CSDL;
class Game{
//Player* pos_1
Player* player_pos_1;
//Player pos_2;
Player* player_pos_2;
unsigned int total_turns;
bool win_cases_loaded;
bool Game_Over;
bool quit_game_from_input;
Grid* game_grid = NULL;
//changed to vector
//std::vector<Win_case*> win_cases;
Win_Case win_cases[8];
CSDL* csdl_obj;
unsigned int turn_phase;

//gameobjects
std::vector<GameObject*> allGameObjects;
GameObject* gameObjectHashTable = NULL;
GameObject* gameObjectTileSelector = NULL;
GameObject* gameObjectGridMarker_A = NULL;
GameObject* gameObjectGridMarker_B = NULL;

// game mode enum

enum current_game_state{menu,gameplay,credits,pause,quit};
public:
Game();
~Game();

Developer debug;
//filter check then mark
bool FilterUserInput(std::string raw_input_string,Position* passed_position);
bool CheckIfTileIsAvailable(Position* passed_position_to_check);
Grid* GetGameGrid(){ return game_grid;}
int GetTurnPhase(){ return turn_phase; }
bool PlayerWin(Player* passed_player);

void LoadWinCases();
Win_Case GetWinCase(int win_case_index);

void MainGameMenu(); //wip
void GameLoop();
void SetGameTileMark(Position* position_to_mark,std::string player_mark);
int PlayerTurn(Player* current_player);
void TurnPhaseEvent();

bool LoadTextureContent();
//switch method calls other methods depending on scene
void GameEventManager();
};
#endif //GAME_H
