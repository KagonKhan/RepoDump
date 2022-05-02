#pragma once
#include "State.h"
#include "gui.h"

class CharacterScreenState : public State {

private:
	//Variables

	sf::Text nameText, statText;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Texture frameTexture;
	sf::RectangleShape frameBackground;



	Player* player;

	sf::Sound sound;
	sf::SoundBuffer buffer;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackgrounds();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initMusic();
	void initPlayerFramePosition();
	void initText();

public:
	CharacterScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Player* player);
	virtual ~CharacterScreenState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

