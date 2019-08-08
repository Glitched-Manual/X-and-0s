#include "GameObject.h"

#ifndef GAMETEXT_H
#define GAMETEXT_H
class GameObject;

class GameText:public GameObject
{
	SDL_Texture* game_text_texture;
	Developer debug;

	SDL_Rect* game_text_rect;
	std::string game_text_id;
	char* game_text_message;
	bool set_text_used = false;
	bool game_text_content_loaded = false;

	unsigned int game_text_box_width;
	unsigned int game_text_box_height;

public:
	GameText(LoaderParams* pParams);
	~GameText();
	//load
	bool LoadGameObjectContent(SDL_Renderer* passed_Renderer);
	//render
	void Draw(SDL_Renderer* passed_Renderer);
	//update? change text?
	void Update();
	//clean
	 void CleanGameObjectContent();

	 std::string GetGameObjectID() { return game_text_id; }
	 bool GetContentLoadedStatus();
	 void SetGameTextMessage(std::string passed_message);
	
};


#endif // GAMETEXT_H