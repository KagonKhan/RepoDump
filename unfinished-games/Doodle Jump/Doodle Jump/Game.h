#pragma once
#include "MainMenuState.h"
#include "GameState.h"



class Game {

	sf::RenderWindow* window;
	sf::Event sfevent;

	std::stack<State*> states;



	void initWindow();
	void initStates();


	void update();
	void updateSFMLEvents();

	void render();

	sf::Clock dtClock;
	float dt;

public:
	Game();
	virtual ~Game();

	void updateDt();
	void run();

};

