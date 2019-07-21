#include "Position.h"
Position::Position()
{
x = new int;
y = new int;
*x = 0;
*y = 0;

}

Position::Position(int passed_x,int passed_y){

x = new int;
y = new int;
*x = passed_x;
*y = passed_y;

}



Position::~Position()
{
	std::cout << "Postion Destroyed" << std::endl;
delete x;
delete y;
}
