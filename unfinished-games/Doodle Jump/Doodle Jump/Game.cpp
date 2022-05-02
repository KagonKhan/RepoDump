#include "Game.h"

Game::Game() {
	initWindow();
	initStates();
}

Game::~Game() {
	delete window;
}


void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Doodle Jump!");
	window->setFramerateLimit(144);
}

void Game::initStates() {
	states.push(new MainMenuState(this->window, &this->states));

}

void Game::update() {

	updateSFMLEvents();


	if (!this->states.empty())
		this->states.top()->update(this->dt);
	else
		window->close();

}

void Game::updateSFMLEvents() {

	while (window->pollEvent(sfevent)) {
		if (sfevent.type == sf::Event::Closed)
			window->close();

	}

}





void Game::render() {

	window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	window->display();

}






void Game::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::run() {

	while (window->isOpen()) {
		updateDt();
		update();
		render();
	}

}