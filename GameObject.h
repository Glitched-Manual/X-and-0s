#include "cross_sdl.h"
#include "LoaderParams.h"
#include "Developer.h"
#include "Color.h"
#include "CCollisionRectangle.h"
#include "Position.h"

#include <string>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
struct Developer;
class CCollisionRectangle;
class GameObject
{
	
	//bool object_content_loaded = false;
public:
	virtual std::string GetGameObjectID() = 0;
	virtual bool LoadGameObjectContent(SDL_Renderer* passed_Renderer) = 0;
	virtual void Draw(SDL_Renderer* passed_renderer) = 0;
	virtual void Update() = 0;
	virtual void CleanGameObjectContent() = 0;

	virtual bool GetContentLoadedStatus() = 0;
	virtual SDL_Texture* GetGameTexture() = 0;

	//if case switches colors for original to other colors and back when recalled
	virtual void ToggleTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value){}

	virtual void AlterTextureColor(Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value){}
	virtual void AlterTextureColor(std::string passed_string,Uint8 passed_r_value, Uint8 passed_g_value, Uint8 passed_b_value) {}
	virtual void RevertAlteredTextureColor(){}
	virtual void RevertAlteredTextureColor(std::string passed_string) {}
	virtual void SetOriginalColors(){}
	virtual Color GetOringinalColors() = 0;
	virtual bool GetAreColorsAltered() { return false; }
	virtual bool GetAreColorsAltered(std::string passed_string) { return false; }
	virtual SDL_Rect* GetTextureRect() = 0;

	
	virtual void AlterTextureAlpha(Uint8 alpha_value, std::string passed_texture_key){}

	//Collision methods
	virtual	CCollisionRectangle* GetCollisionRectangle() { return NULL; }

	virtual bool CheckCollisionPoints(CCollisionRectangle* passed_CollisionRectangle) { return false; }
	virtual bool HasObjectCollided(CCollisionRectangle* passed_first_CollisionRectangle, CCollisionRectangle* passed_second_CollisionRectangle) { return false; }
	GameObject(){}
protected:

	GameObject(LoaderParams* pParams){}
	virtual ~GameObject(){}

};
static unsigned int staic_prompt_option_selector = 0;
#endif //GAMEOBJECT_H