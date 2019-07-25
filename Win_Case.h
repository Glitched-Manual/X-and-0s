#include <iostream>
#include <string>
#include "Position.h"

#ifndef WIN_CASE_H
#define WIN_CASE_H
class Position;
class Win_Case{

Position* combination[3];
//std::shared_ptr<Position[]> combination = std::make_shared<Position[]>(3);;
std::string win_case_id;

public:
Win_Case();
~Win_Case();
void SetWinCaseCombination(Position first_position, Position second_position,Position third_position);

Position* GetCombination(int passed_index);

std::string GetWinCaseID(){ return win_case_id; }

};
#endif //WIN_CASE_H
