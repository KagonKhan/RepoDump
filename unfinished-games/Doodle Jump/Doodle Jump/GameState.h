#pragma once
#include "State.h"
#include "Player.h"
#include "Platform.h"
#include "HighscoreState.h"

class GameState : public State {

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	Platform* platforms[10];
	Player player;
	sf::Font font;

	void initButtons();
	void initBackground();
	void initPlatforms();
	std::string scorestring;
	void updateMovement(const float& dt);

	sf::Vector2f direction;

	sf::RectangleShape floor;

	int lastJump = 90000;
	bool lost = false;
	int highscore = 0;

	sf::Text highscoreText;

	sf::Clock highscoreClock;
	void updateHighscore();
	void initText();
	

	bool startHighscore = false;
public:

	GameState(sf::RenderWindow* window, std::stack <State*>* states);
	virtual ~GameState();


	void update(const float& dt);


	void render();


};

