#include "iostream"
#include "string"
#include "Position.h"

#ifndef "WIN_CASE_H"
#define "WIN_CASE_H"
class Position;
class Win_Case{

Position combination[3];

std::string win_case_id;

public:

void SetPositionCombination();

Position* GetCombination(){ return combination; }

std::string GetWinCaseID(){ return win_case_id; }

};
#endif //WIN_CASE_H
