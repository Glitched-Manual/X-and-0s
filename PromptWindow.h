#include "CSDL.h"
#include "GameObject.h"
#include "Developer.h"
#include "GameText.h"

#include <map>
#include <string>
#include <vector>
#include <cmath>
#ifndef PROPMTWINDOW_H
#define PROPMTWINDOW_H

//forward declaration

class CSDL;
class LoaderParams;

struct Developer;
// class definition

class PromptWindow: public GameObject
{
	std::map<std::string, SDL_Texture*> prompt_texture_map;

	//clip names are names based or the key of the texture it belongs to.

	//ie: "key" + "_clip"

	std::map<std::string, SDL_Rect*> prompt_texture_rect_map;

	std::vector<GameText*> game_texts_vector;
	std::map<std::string,GameText*> game_texts_map;

	std::string base_background_texture_key;

	std::string prompt_window_id;

	Color prompt_background_color;

	bool prompt_window_content_loaded = false;
	bool prompt_window_colors_altered = false;
	CSDL* csdl_obj;

	
public:

	PromptWindow(LoaderParams* pParams, CSDL* passed_csdl_obj);
	~PromptWindow();

	 std::string GetGameObjectID() { return NULL; }
	 bool LoadGameObjectContent(SDL_Renderer* passed_Renderer);
	 void Draw(SDL_Renderer* passed_Renderer);
	 void Update();
	 void CleanGameObjectContent();

	 bool GetContentLoadedStatus() { return NULL; }
	 SDL_Texture* GetGameTexture() { return NULL; }

	//if case switches colors for original to other colors and back when recalled
	 void ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);

	 void AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	 void AlterTextureColor(std::string passed_string,Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value);
	 void RevertAlteredTextureColor();
	 void RevertAlteredTextureColor(std::string passed_string);
	 void SetOriginalColors();
	 Color GetOringinalColors() { return prompt_background_color; }
	
	 bool GetAreColorsAltered() { return prompt_window_colors_altered; }

	 bool GetAreColorsAltered(std::string passed_string);
	 SDL_Rect* GetTextureRect() { return NULL; }
	 
	 void AlterTextureAlpha(Uint8 alpha_value, std::string passed_texture_key);

	 //methods not in game object class

	 bool CreateBackGroundTexture(SDL_Renderer* passed_renderer);

	 bool CreatePromptText(unsigned int passed_percent_x, unsigned int passed_percent_y, std::string passed_text_id, std::string passed_message, unsigned int text_size);

};


#endif //PROPMTWINDOW_H