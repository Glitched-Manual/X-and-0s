#include "HashTable.h"


HashTable::HashTable(const LoaderParams* pParams)
{
	//set everything from params
	hash_table_rect = new SDL_Rect;

	hash_table_rect->x = pParams->GetX() - ( pParams->GetWidth() /2 );
	hash_table_rect->y = pParams->GetY() - ( pParams->GetHeight() / 2 );
	hash_table_rect->w = pParams->GetWidth();
	hash_table_rect->h = pParams->GetHeight();

	SetCollisionRectVector();
}


bool HashTable::LoadGameObjectContent(SDL_Renderer* passed_Renderer)
{
	hash_table_texture = IMG_LoadTexture(passed_Renderer,"resources/images/table_image_2.png");

	if (hash_table_texture == NULL)
	{
		if (Developer::GetInstance()->is_debug_mode())
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
		return false;
	}

	if (Developer::GetInstance()->is_debug_mode())
	{
		printf("HashTable was successfully loaded\n");
	}
	//load hit box
	hash_table_hit_box = new HitBox(passed_Renderer);
	hash_table_hit_box->LoadTexture(passed_Renderer);

	hash_table_content_loaded = true;
	return true;
}

void HashTable::Draw(SDL_Renderer* passed_Renderer)
{
	
	SDL_RenderCopyEx(passed_Renderer, hash_table_texture,NULL, hash_table_rect,0,NULL,SDL_FLIP_NONE);
	if (Developer::GetInstance()->are_hit_boxes_rendered())
	{
		for (std::vector<CCollisionRectangle*>::iterator collider_index = collision_rects_vector.begin(); collider_index != collision_rects_vector.end(); collider_index++)
		{

			hash_table_hit_box->RenderGameObjectHitBox(passed_Renderer, (*collider_index)->GetCollisionRect());
		}
	}
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

	int w_value = ( (hash_table_rect->w / 6) * 2);

	int h_value = ( (hash_table_rect->h / 6) * 2);

	//give values to collisions rect

	collision_obj->SetCollisionRect(x_value, y_value, w_value, h_value);

	collision_rects_vector.push_back(collision_obj);
	//add to collider map
	collider_position_map[collision_obj] = new Position(passed_x, passed_y);
}

bool HashTable::CheckCollisionPoints(CCollisionRectangle* passed_CollisionRectangle)
{ 
	// good if the object only has I collider

	return false; 
}

bool HashTable::HasObjectCollided(CCollisionRectangle* prime_collider, CCollisionRectangle* alpha_collider) // forgot to put bools in if statement
{

	//x,y
	if (PointCollisionCheck(prime_collider->GetCollisionRect()->x, prime_collider->GetCollisionRect()->y, alpha_collider))
	{
		return true;
	}
	//x+w,y
	if (PointCollisionCheck(prime_collider->GetCollisionRect()->x + prime_collider->GetCollisionRect()->w, prime_collider->GetCollisionRect()->y, alpha_collider))
	{
		return true;
	}
	//x,y+h
	if (PointCollisionCheck(prime_collider->GetCollisionRect()->x, prime_collider->GetCollisionRect()->y + prime_collider->GetCollisionRect()->h, alpha_collider))
	{
		return true;
	}
	//x+w,y+h
	if (PointCollisionCheck(prime_collider->GetCollisionRect()->x + prime_collider->GetCollisionRect()->w, prime_collider->GetCollisionRect()->y + prime_collider->GetCollisionRect()->h, alpha_collider))
	{
		return true;
	}


	return false;
}

/*
   1 _ 2
    |_|
   3   4

   1(x,y)

   obj 2

   A _ B
	|_|
   C   D

   check 1-4

   by checking if each x,y is within

      <-------X--> 
      ___________
   ^ |
   | |
   Y |
   | |
   v

     AND

	      | ^
		  | |
		  | Y
	______| |
	<--X--> v

*/


bool HashTable::PointCollisionCheck(int x, int y, CCollisionRectangle* alpha_collider)
{

	if ((x >= alpha_collider->GetCollisionRect()->x) && (y >= alpha_collider->GetCollisionRect()->y))
	{

		if (x >= (alpha_collider->GetCollisionRect()->x + alpha_collider->GetCollisionRect()->w))
		{

			if (y >= (alpha_collider->GetCollisionRect()->y + alpha_collider->GetCollisionRect()->h))
			{
				return true;
			}
		}
	}
	return false;
}

Position* HashTable::GetPositionOfSelectedTile(CCollisionRectangle* passed_CollisionRectangle)
{
	
	//vector for loop

	for (auto vec : collision_rects_vector)
	{
		if (HasObjectCollided(passed_CollisionRectangle,vec))
		{
			if(Developer::GetInstance()->is_debug_mode())
			{
				puts("HashTable::GetPositionOfSelectedTile - Collision with Hash table detected\n");
			}
			return collider_position_map[vec];
		}
			
	}
	if (Developer::GetInstance()->is_debug_mode())
	{
		puts("HashTable::GetPositionOfSelectedTile - Collision with Hash table Returning NULL\n");
	}

	return NULL;
}