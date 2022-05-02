#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <stack>
#include "Button.h"

class State {

protected:
	std::stack<State*>* states; //wskaznik do stosu w ktorym sa wskazniki
	sf::RenderWindow* window;

	sf::Vector2f mousePosition;


public:
	State(sf::RenderWindow* window, std::stack <State*>* states);
	virtual ~State();


	virtual void update(const float& dt) = 0;
	virtual void render() = 0;


	virtual void updateMousePos();

};

