#include "GameObject.h"

#ifndef GAMETEXT_H
#define GAMETEXT_H
class GameObject;

class GameText:public GameObject
{
	SDL_Texture* game_text_texture;
	

	SDL_Rect* game_text_rect;
	std::string game_text_id;
	char* game_text_message;
	bool set_text_used = false;
	bool game_text_content_loaded = false;
	bool game_text_message_highlighted = false;

	unsigned int game_text_size = 20; //default
	unsigned int game_text_box_width;
	unsigned int game_text_box_height;

	Color game_text_original_color;

public:
	GameText(LoaderParams* pParams);
	GameText(LoaderParams* pParams, unsigned int text_size);
	GameText(LoaderParams* pParams, std::string message, unsigned int text_size);
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
	 void SetGameTextMessage(char* passed_message);
	 SDL_Texture* GetGameTexture() { return game_text_texture; }

	 void AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	 void RevertAlteredTextureColor();

	  void SetOriginalColors();
	  Color GetOringinalColors();

	  void ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	  bool GetAreColorsAltered() { return game_text_message_highlighted; } //if hightlighted true 
	  SDL_Rect* GetTextureRect() { return game_text_rect; }
};


#endif // GAMETEXT_H