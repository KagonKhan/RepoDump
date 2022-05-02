#include "stdafx.h"
#include "Game.h"
//Static functions

//Constructor functions
Game::Game(){
	/*Initialize the game window as game object is created*/
	this->initWindow();
	this->initKeys();
	srand((time)(NULL));
	this->initStates(); 
}

Game::~Game() {
	/*autodestruct pointer, maybe usage of smart pointers?/ unique*/
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

//Initializer functions

void Game::initVariables(){
	this->window = nullptr;
	this->dt = 0.f;
	this->fullscreen = false;
}

void Game::initWindow() {
	/*Create the window with specified stats in config ini file*/

	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();



	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

	unsigned antialiasing_level = 0;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	bool fullscreen = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	windowSettings.antialiasingLevel = antialiasing_level;
	this->fullscreen = fullscreen;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);


}







void Game::initKeys() {

	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
			this->supportedKeys[key] = key_value;
	}

	ifs.close();


}

void Game::initStates(){
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Functions
void Game::updateDt(){
	/*Updates the dt variable with time it takes to update and render - frame time*/
	this->dt = this->dtClock.restart().asSeconds();
	system("cls");
//	std::cout << 1/this->dt << "\n";
}

void Game::updateSFMLEvents(){

	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update(){
	this->updateSFMLEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		
		if (this->states.top()->getQuit()) {

			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else {
		this->endApplication();
		this->window->close();
	}

}

void Game::render(){
	//Clear frame
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render(this->window);


	//render frame
	this->window->display();
}

void Game::run(){
	/*Main game loop - updating, rendering etc, as long as window is open*/
	while (this->window->isOpen()) {


		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::endApplication(){
	std::cout << "ending app!\n";
}