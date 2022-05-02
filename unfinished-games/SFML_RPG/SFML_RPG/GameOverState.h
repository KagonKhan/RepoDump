#pragma once
#include "State.h"
#include "gui.h"

class GameOverState : public State {

private:
	//Variables

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	Player* player;
	std::map<std::string, gui::Button*> buttons;

	sf::Text gameOverText;

	//Functions
	void initVariables();
	void initBackgrounds();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initText();

public:
	GameOverState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameOverState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

