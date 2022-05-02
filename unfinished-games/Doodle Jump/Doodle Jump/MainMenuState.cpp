#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {
	initButtons();
	initBackground();
}

MainMenuState::~MainMenuState() {
	for (auto it : buttons)
		delete it.second; 

}



void MainMenuState::initButtons() { 
	buttons["START"] = new Button(sf::Vector2f((window->getSize().x - 150) / 2, 100), sf::Color::Green);
	buttons["HIGH_SCORES"] = new Button(sf::Vector2f((window->getSize().x - 150) / 2, 250), sf::Color::Yellow);
	buttons["EXIT"] = new Button(sf::Vector2f((window->getSize().x - 150) / 2, 400), sf::Color::Red);

}

void MainMenuState::initBackground() {
	background.setSize(sf::Vector2f(window->getSize()));
	background.setFillColor(sf::Color::Cyan);

}





void MainMenuState::update(const float& dt) {
	updateButtons();
	updateMousePos();

}

void MainMenuState::updateButtons() {

	for (auto it : buttons)
		it.second->update(mousePosition);
	


	if (buttons["START"]->isButtonPressed()) {
		states->push(new GameState(this->window, this->states));
	}


	if (buttons["HIGH_SCORES"]->isButtonPressed()) {
	}


	if (buttons["EXIT"]->isButtonPressed()) {
	}

}





void MainMenuState::render() {


	window->draw(background);
	renderButtons();

}



void MainMenuState::renderButtons() {
	for (auto ita : buttons)
		ita.second->render(this->window);

}


