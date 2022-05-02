#pragma once

#include <iostream>

#include <SDL.h>
#include <glew.h>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "GLTexture.h"
#include <vector>


enum class GameState {PLAY, EXIT};

class MainGame {
	SDL_Window* _window;
	int _screenWidth, _screenHeight; // _ means private var

	GameState _gameState;


	std::vector<Sprite*> _sprites;

	GLSLProgram _colorProgram;


	float _time, _fps, _frameTime, _maxFPS;




	void initSystems();
	void initShaders();

	void processInput();

	void drawGame();

	void gameLoop();


	void calculateFPS();



public:
	MainGame();
	~MainGame();


	void run();

};

