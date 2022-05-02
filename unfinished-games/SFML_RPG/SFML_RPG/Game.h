#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;



	sf::ContextSettings windowSettings;

	std::vector<sf::VideoMode> videoModes;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;


	float dt;

	bool fullscreen;
	
	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();


public:
	//Constructors Destructors
	Game();
	virtual ~Game();



	//Functions
	
	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();


	//Render
	void render();

	//Core
	void run();
};

