#include "cross_sdl.h"
#include "LoaderParams.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{

	//bool object_content_loaded = false;
public:
	virtual bool LoadGameObjectContent() = 0;
	virtual void Draw(SDL_Renderer* passed_Renderer) = 0;
	virtual void Update() = 0;
	virtual void CleanGameObjectContent() = 0;

	virtual bool GetContentLoadedStatus() = 0;

protected:

	GameObject(const LoaderParams* pParams){}
	virtual ~GameObject(){}

};

#endif //GAMEOBJECT_H