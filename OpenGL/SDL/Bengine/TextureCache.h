#pragma once

#include <map>
#include <string>
#include "GLTexture.h"

class TextureCache {

	std::map<std::string, GLTexture> _textureMap;


public:

	TextureCache() {};
	~TextureCache(){};


	GLTexture getTexture(std::string texturePath);





};

