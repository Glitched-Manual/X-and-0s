#include "CSDL.h"
#include "GameObject.h"
#include <map>
#include <string>

#ifndef PROPMTWINDOW_H
#define PROPMTWINDOW_H

//forward declaration

class CSDL;

// class definition

class PromptWindow: public GameObject
{
	std::map<std::string, SDL_Texture*> prompt_texture_vector;

	//clip names are names based or the key of the texture it belongs to.

	//ie: "key" + "_clip"

	
	std::map<std::string, SDL_Rect*> prompt_texture_rect_vector;

	std::string base_background_texture_key;
public:

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
	 void RevertAlteredTextureColor();
	 void SetOriginalColors();

	 bool GetAreColorsAltered() { return NULL; }
	 SDL_Rect* GetTextureRect() { return NULL; }


	 void AlterTextureAlpha(Uint8 alpha_value, std::string passed_texture_key);


};


#endif //PROPMTWINDOW_H