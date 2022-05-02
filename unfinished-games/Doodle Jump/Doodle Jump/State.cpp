#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
	this->window = window;
	this->states = states;

}

State::~State() {

}

void State::updateMousePos() {
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}
