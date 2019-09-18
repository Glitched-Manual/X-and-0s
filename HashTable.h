#include "GameObject.h"
#include "CCollisionRectangle.h"
#include "HitBox.h"
#include <vector>
#include <map>
#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable: public GameObject
{
	SDL_Texture* hash_table_texture = NULL;
	SDL_Rect* hash_table_rect = NULL;
	std::string hash_table_id;
	
	bool hash_table_content_loaded = false;
	bool colors_altered = false;

	Color hash_table_original_color;
	

	std::vector< CCollisionRectangle*> collision_rects_vector;
	std::map<CCollisionRectangle*, Position*> collider_position_map;
	HitBox* hash_table_hit_box; // make as singleton

public:
	 HashTable(const LoaderParams* pParams);
	 bool LoadGameObjectContent(SDL_Renderer* passed_Renderer);
	 void Draw(SDL_Renderer* passed_Renderer);
	 void Update();
	 void CleanGameObjectContent();
	 bool GetContentLoadedStatus() { return hash_table_content_loaded; }
	 std::string GetGameObjectID() { return hash_table_id;	 }

	 SDL_Texture* GetGameTexture() { return hash_table_texture; }

	 	
	 //if case switches colors for original to other colors and back when recalled
	  void ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);

	  void AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	  void RevertAlteredTextureColor();
	  void SetOriginalColors();
	  Color GetOringinalColors() { return hash_table_original_color; }
	  bool GetAreColorsAltered() { return colors_altered; }
	  SDL_Rect* GetTextureRect() { return hash_table_rect;   }

	  //Collision methods

	 void SetCollisionRectVector();
	 void CreateCollisionRectangle(unsigned int x,unsigned int y);

	 bool CheckCollisionPoints(CCollisionRectangle* passed_CollisionRectangle);
	 bool HasObjectCollided(CCollisionRectangle* passed_first_CollisionRectangle, CCollisionRectangle* passed_second_CollisionRectangle);
	 bool PointCollisionCheck(int x,int y, CCollisionRectangle* passed_second_CollisionRectangle);

	 Position* GetPositionOfSelectedTile(CCollisionRectangle* passed_CollisionRectangle);
	 
};

#endif //HASHTABLE_H