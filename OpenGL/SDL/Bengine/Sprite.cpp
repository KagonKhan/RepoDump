#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>


Sprite::Sprite() {
	_vboID = 0;
}

Sprite::~Sprite() {
	if (_vboID)
		glDeleteBuffers(1, &_vboID);
}
	

void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = ResourceManager::getTexture(texturePath);



	if (!_vboID) //if not set, set
		glGenBuffers(1, &_vboID); // generate 1buffer (Vertex Buffer Object)
	

	Vertex vertexData[6]; // points on screen, 6 vertices for a square, each x y coords


	vertexData[0].setPosition(x + width, y + width);
	vertexData[0].setUV(1.f, 1.f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.f, 1.f);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.f, 0.f);

	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.f, 0.f);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.f, 0.f);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.f, 1.f);

	//COLOR
	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 255, 255, 255);
	}

	//	vertexData[1].color.r = 0;

	//vertexData[4].setColor(0, 255, 0, 255);


	glBindBuffer(GL_ARRAY_BUFFER, _vboID); // have to bind
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {


	//dont unbind 
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	//THIS IS THE POSITION ATTRIBUTE POINTER
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //which buffer, size of vertex, type of, 

	//COLOR ATTRIBUTE POINTER 
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//UV ATTRIBUTE POINTER 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));



	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
