#include <iostream>
#include <string>
#include "Player.h"

#ifndef AI_H
#define AI_H
class Player;

class AI:public Player
{

public:

	AI();
	AI(const AI& obj);
	~AI();
};

#endif //AI_H
