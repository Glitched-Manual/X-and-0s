#include <iostream>
#include <string>

#ifndef POSITION_H
#define POSITION_H

class Position{
public:
Position(){}
Position(int passed_x,int passed_y){ *x = passed_x; *y = passed_y;}
int* x;
int* y;
};
#endif //POSITION_H
