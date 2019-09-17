#include <iostream>
#include <string>
#include <memory>
#include "Developer.h"
#include <memory>

#ifndef POSITION_H
#define POSITION_H

struct Developer;

class Position{
public:
Position();
Position(int passed_x,int passed_y);
~Position();
 const int* GetX(){ return x;}
 const int* GetY(){ return y;}


void SetX(int passed_x){ *x = passed_x;}
void SetY(int passed_y){ *y = passed_y;}
void SetPositionXY(int passed_x, int passed_y);

private:
int* x;
int* y;
};

#endif //POSITION_H


