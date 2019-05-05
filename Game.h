#ifndef "GAME_H"
#define "GAME_H"

class Game{

bool Game_Over;

Grid* game_grid;

Win_Case win_cases[8];
unsigned int turn_phase;
public:
Game();

Grid* GetGameGrid(){ return game_grid;}
int GetTurnPhase(){ return turn_phase; }
void PlayerWin(Position passed_position);

void LoadWinCases();

void GameLoop();

};
#endif //GAME_H
