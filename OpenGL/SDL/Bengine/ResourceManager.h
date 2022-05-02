#pragma once
#include "TextureCache.h"
#include <string>

class ResourceManager {

	static TextureCache _textureCache;





public:
	ResourceManager() = delete;
	~ResourceManager() = delete;


	//This is just a wrapper
	static GLTexture getTexture(std::string texturePath);





};

