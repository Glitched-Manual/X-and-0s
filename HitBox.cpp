#include "HitBox.h"

HitBox::HitBox()
{

}
HitBox::HitBox(SDL_Renderer* passed_renderer)
{
	game_renderer = passed_renderer;
}
HitBox::~HitBox()
{

}


bool HitBox::LoadTexture()
{

}

void HitBox::SetRenderer(SDL_Renderer* passed_renderer)
{
	game_renderer = passed_renderer;
}
void HitBox::RenderGameObjectHitBox(SDL_Rect* passed_collision_rect)
{
	SDL_RenderCopyEx(game_renderer, hit_box_texture, texture_crop_rect, passed_collision_rect, 0, NULL, SDL_FLIP_NONE);
}