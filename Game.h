#include <memory>
#include <vector>
#include <map>

#include "Grid.h"
#include "Win_Case.h"
#include "Player.h"
#include "AI.h"
#include "CSDL.h"
#include "HashTable.h"
#include "GameText.h"

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
GameObject* gameObjectGridMarker = NULL;


std::map<std::string, GameObject* > game_object_map;

// game mode enum

enum current_game_state {main_menu,game_options,gameplay,credits,pause,quit};
enum current_gameplay_mode {human_vs_human,human_vs_computer};

current_game_state x_o_game_state;
current_gameplay_mode x_o_gameplay_mode;

//screen dimensions
unsigned int SCREEN_WIDTH;

unsigned int SCREEN_HEIGHT;

public:
Game(unsigned int passed_screen_width, unsigned int passed_screen_height);
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

bool LoadGameObjectContent();

bool LoadGameOpeningMenu();
//switch method calls other methods depending on scene
void GameEventManager();

void RenderGameTextures();
};
#endif //GAME_H
