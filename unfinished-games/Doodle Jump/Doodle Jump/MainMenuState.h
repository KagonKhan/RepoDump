#pragma once
#include "State.h"

class MainMenuState: public State {

	sf::RectangleShape background;
	std::map<std::string, Button*> buttons;


public:

	MainMenuState(sf::RenderWindow* window, std::stack <State*>* states);
	virtual ~MainMenuState();


	void initButtons();
	void initBackground();


	void update(const float& dt);
	void updateButtons();

	void render();
	void renderButtons();


};

