#pragma once
#include "State.h"
class HighscoreState : public State {

	sf::Font font;
	sf::Text highscoreText;
	std::string text;

	sf::RectangleShape backgroundShape;
	sf::RectangleShape middleShape;


	void initBackground();
	void updateText(int score);



public:
	HighscoreState(sf::RenderWindow* window, std::stack <State*>* states, int score, bool write = false);
	~HighscoreState() {};
	
	void update(const float& dt);
	void render();
};

