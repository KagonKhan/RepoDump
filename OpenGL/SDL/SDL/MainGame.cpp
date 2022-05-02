#include "MainGame.h"

#include "Errors.h"


MainGame::MainGame() 
	: _window(nullptr),
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_time(0.f),
	_fps(0.f),
	_frameTime(0.f),
	_maxFPS(75.f) {}


MainGame::~MainGame() {
}

void MainGame::run() {
	initSystems();

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.f, -1.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.f, 0.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.f, -1.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.f, 0.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");




	gameLoop();
}

void MainGame::initSystems() {
	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // have 2 window buffers


	_window = SDL_CreateWindow("Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (!_window)
		fatalError("STL Window could not be created!");


	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (!glContext)
		fatalError("SD_GL Context could not ve created!");


	GLenum error = glewInit(); // returns 0 if no errors

	if (error)
		fatalError("Could not initialize glew!");

	// current gl version
	printf("***     OpenGL Version: %s   ***\n", glGetString(GL_VERSION));


	glClearColor(0.f, 0.f, 1.f, 1.f);

	initShaders();

}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::processInput() {

	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))// return boolean if there is event
		switch (sdlEvent.type) {


		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;


		case SDL_MOUSEMOTION:


			break;


		}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	_colorProgram.use();
	

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	glActiveTexture(GL_TEXTURE0);





	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);



	for(auto it: _sprites)
		it->draw();







	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();


	SDL_GL_SwapWindow(_window);

}



void MainGame::gameLoop() {

	while (_gameState != GameState::EXIT) {

		float startTicks = SDL_GetTicks();


		processInput();
		_time += 0.001f;
		drawGame();
		calculateFPS();


		//Print every 10 frames
		static int framecounter = 0;
		framecounter++;
		if (framecounter == 10) {
			std::cout << _fps << std::endl;
			framecounter = 0;
		}

		//Limit FPS to max

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.f / _maxFPS > frameTicks)
			SDL_Delay(1000.f / _maxFPS - frameTicks);

	}


}


//Holy fucking aids, why
void MainGame::calculateFPS() {
	static const int NUM_OF_SAMPLES = 10;
	static float frameTimes[NUM_OF_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();


	_frameTime = currentTicks - prevTicks;
	prevTicks = currentTicks;

	//Circular container
	frameTimes[currentFrame % NUM_OF_SAMPLES] = _frameTime;

	currentFrame++;

	int count;
	currentFrame < NUM_OF_SAMPLES ? count = currentFrame : count = NUM_OF_SAMPLES;

	float frameTimeAverage = 0;


	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];
	


	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.f / frameTimeAverage;



}
