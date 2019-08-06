#include "GameObject.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable: public GameObject
{
	SDL_Texture* hash_table_texture = NULL;
	SDL_Rect* hash_table_rect = NULL;
	Developer debug;
	bool object_content_loaded = false;
protected:
	


public:
	 HashTable(const LoaderParams* pParams);
	 bool LoadGameObjectContent(SDL_Renderer* passed_Renderer);
	 void Draw(SDL_Renderer* passed_Renderer);
	 void Update();
	 void CleanGameObjectContent();
	 bool GetContentLoadedStatus();
};

#endif //HASHTABLE_H