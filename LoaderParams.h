#include <iostream>
#include <string>


#ifndef LOADERPARAMS_H
#define LOADERPARAMS_H

class LoaderParams
{
	unsigned int obj_x;
	unsigned int obj_y;

	unsigned int obj_width;
	unsigned int obj_height;

	std::string obj_textureID;

public:

	LoaderParams(unsigned int passed_x, unsigned int passed_y, unsigned int passed_width, unsigned int passed_height, std::string passed_textureID);

	unsigned int GetX() const { return obj_x; }
	unsigned int GetY() const { return obj_y; }
	unsigned int getWidth() const { return obj_width; }
	unsigned int getHeight() const { return obj_height; }
	std::string getTextureID() const { return obj_textureID; }
};

#endif // LOADERPARAMS_H