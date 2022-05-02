#pragma once

#include "glew.h"
#include "GLTexture.h"
#include <string>
#include "ResourceManager.h"


class Sprite {
	float _x, _y, _width, _height;

	GLuint _vboID; // unsigned int guaranteed 32 bits

	GLTexture _texture;



public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);

	void draw();

};

