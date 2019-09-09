#include "GameObject.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable: public GameObject
{
	SDL_Texture* hash_table_texture = NULL;
	SDL_Rect* hash_table_rect = NULL;
	std::string hash_table_id;
	Developer debug;
	bool hash_table_content_loaded = false;
	bool colors_altered = false;

	Color hash_table_original_color;
	CCollisionRectangle* hash_table_collision_rect = NULL;
protected:
	


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
};

#endif //HASHTABLE_H