#pragma once
#include "State.h"
#include "TownState.h"
#include "PauseMenu.h"
#include "GameOverState.h"
#include "CharacterScreenState.h"

enum whichEntity{PLAYER = 0, ENEMY};

class GameState : public State {
private:


	bool playerRound;
	bool showMissText;
	int missTextColorR, missTextColorG, missTextColorB, missTextColorA;
	float missXwavePos, missYwavePos;

	Player* player;
	Enemy* enemy;
	PauseMenu* pMenu;
	sf::Font font;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	std::map<std::string, gui::Button*> buttons;
	
	//maybe a map, not sure if will be usefull so far
	sf::Texture bgTextures[4];
	sf::Texture test;

	sf::Text missText;


	sf::RectangleShape background;
	sf::RectangleShape statBox;

	sf::Text statText;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initEnemy();
	void initFonts();
	void initPauseMenu();
	void initBackground();
	void initButtons();
	void initStatBox();
	void initMusic();
	void initText();
	void initVariables();




	void checkHit(bool type, int attackType, const float& dt);
	void attack(bool type, int attackType, const float& dt);
	void enemyAttack(bool type, const float& dt);

	float timeCounter;

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	virtual ~GameState();

	//Functions

	void updateButtons(const float& dt);
	void renderButtons(sf::RenderTarget& target);

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void updateAnimations(const float& dt);
	void updateText(const float& dt);
	void render(sf::RenderTarget* target = nullptr);



	void renderMissText(const float& dt);
};