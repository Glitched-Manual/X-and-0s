#include "cross_sdl.h"
#include "LoaderParams.h"
#include "Developer.h"
#include <string>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
struct Developer;
class GameObject
{

	//bool object_content_loaded = false;
public:
	virtual std::string GetGameObjectID() = 0;
	virtual bool LoadGameObjectContent(SDL_Renderer* passed_Renderer) = 0;
	virtual void Draw(SDL_Renderer* passed_Renderer) = 0;
	virtual void Update() = 0;
	virtual void CleanGameObjectContent() = 0;

	virtual bool GetContentLoadedStatus() = 0;
	GameObject(){}
protected:

	GameObject(LoaderParams* pParams){}
	virtual ~GameObject(){}

};

#endif //GAMEOBJECT_H