#include "cross_sdl.h"
#include "GameObject.h"

#ifndef CCOLLISIONRECTANGLE_H
#define CCOLLISIONRECTANGLE_H

class CCollisionRectangle
{
	SDL_Rect* CollisionRect = NULL;
public:
	CCollisionRectangle();
	CCollisionRectangle(int x, int y, int w, int h);
	~CCollisionRectangle();
	void SetCollisionRect(int x,int y, int w, int h);
	SDL_Rect* GetCollisionRect() { return CollisionRect; }
};


#endif //CCOLLISIONRECTANGLE_H