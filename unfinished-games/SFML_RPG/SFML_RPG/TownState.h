#pragma once
#include "State.h"
#include "gui.h"

class TownState : public State {

private:
	//Variables

	sf::Sound snoreSound;
	sf::SoundBuffer buffer;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	Player* player;
	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackgrounds();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	TownState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Player* player);
	virtual ~TownState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

