#pragma once
#include "GameState.h"
#include "gui.h"
#include "EditorState.h"
#include "SettingsState.h"
class MainMenuState : public State {
	
private:
	//Variables
	sf::Music bgMusic;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackgrounds();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initMusic();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

