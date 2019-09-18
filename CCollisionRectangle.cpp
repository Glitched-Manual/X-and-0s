#include "CCollisionRectangle.h"

CCollisionRectangle::CCollisionRectangle()
{
	CollisionRect = new SDL_Rect;
}

CCollisionRectangle::CCollisionRectangle(int passed_x, int passed_y, int passed_w, int passed_h)
{
	CollisionRect = new SDL_Rect;

	CollisionRect->x = passed_x;
	CollisionRect->y = passed_y;
	CollisionRect->w = passed_w;
	CollisionRect->h = passed_h;
}


CCollisionRectangle::~CCollisionRectangle()
{

}

void CCollisionRectangle::SetCollisionRect(int passed_x, int passed_y, int passed_w, int passed_h)
{

	CollisionRect->x = passed_x;
	CollisionRect->y = passed_y;
	CollisionRect->w = passed_w;
	CollisionRect->h = passed_h;

}

void CCollisionRectangle::MoveCollisionRect(int passed_x, int passed_y)
{
	CollisionRect->x = passed_x;
	CollisionRect->y = passed_y;
}