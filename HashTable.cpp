#include "HashTable.h"


HashTable::HashTable(const LoaderParams* pParams)
{
	//set everything from params
	hash_table_rect = new SDL_Rect;

	hash_table_rect->x = pParams->GetX() - ( pParams->GetWidth() /2 );
	hash_table_rect->y = pParams->GetY() - ( pParams->GetHeight() / 2 );
	hash_table_rect->w = pParams->GetWidth();
	hash_table_rect->h = pParams->GetHeight();

	
}


bool HashTable::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{
	hash_table_texture = IMG_LoadTexture(passed_Renderer,"resources/images/table_image_2.png");

	if (hash_table_texture == NULL)
	{
		if (debug.is_debug_mode())
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
		return false;
	}

	if (debug.is_debug_mode())
	{
		printf("HashTable was successfully loaded\n");
	}
	hash_table_content_loaded = true;
	return true;
}

void HashTable::Draw(SDL_Renderer* passed_Renderer)
{
	
	SDL_RenderCopyEx(passed_Renderer, hash_table_texture,NULL, hash_table_rect,0,NULL,SDL_FLIP_NONE);

}
void HashTable::Update()
{

}
void HashTable::CleanGameObjectContent()
{

}

void HashTable::SetOriginalColors()
{

}

void HashTable::RevertAlteredTextureColor()
{


}

void HashTable::AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{


}

void HashTable::ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value)
{

}

void HashTable::SetCollisionRectVector()
{
	/*
	Sets a CCollision object for each tile in the 3x3 hash table
	*/

	for (unsigned int x_cord = 0; x_cord < 3; x_cord++)
	{
		for (unsigned int y_cord = 0; y_cord < 3; y_cord++)
		{
			CreateCollisionRectangle(x_cord, y_cord);
		}
	}

}

void HashTable::CreateCollisionRectangle(unsigned int passed_x, unsigned int passed_y)
{
	//make new CCollision* obj

	CCollisionRectangle* collision_obj = new CCollisionRectangle;

	/*
	
	
	
	
	*/

	int x_value = hash_table_rect->x + ( (hash_table_rect->w / 6) * (passed_x * 2) );

	int y_value = hash_table_rect->y + ( (hash_table_rect->h / 6) * (passed_y * 2) );

	int w_value = x_value + ( (hash_table_rect->w / 6) * 2);

	int h_value = y_value + ( (hash_table_rect->h / 6) * 2);

	//give values to collisions rect

	collision_obj->SetCollisionRect(x_value, y_value, w_value, h_value);

	collision_rects_vector.push_back(collision_obj);
}