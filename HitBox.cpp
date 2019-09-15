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


bool HitBox::LoadTexture(SDL_Renderer* passed_renderer)
{
	//load a colored background from a texture or a image with a x

	hit_box_texture = IMG_LoadTexture(passed_renderer, "resources/images/hit_box_image001.png"); //forgot to add .png

	if (hit_box_texture == NULL)
	{
		if (debug.is_debug_mode())
		{
			std::cout << "HitBox::LoadTexture() error - " << IMG_GetError() << std::endl;
		}
		return false;
	}
	return true;
}

void HitBox::SetRenderer(SDL_Renderer* passed_renderer)
{
	game_renderer = passed_renderer;
}

void HitBox::RenderGameObjectHitBox(SDL_Rect* passed_collision_rect)
{
	SDL_RenderCopyEx(game_renderer, hit_box_texture, NULL, passed_collision_rect, 0, NULL, SDL_FLIP_NONE);
}


void HitBox::RenderGameObjectHitBox(SDL_Renderer* passed_renderer, SDL_Rect* passed_collision_rect)
{
	SDL_RenderCopyEx(passed_renderer, hit_box_texture, NULL, passed_collision_rect, 0, NULL, SDL_FLIP_NONE);
}