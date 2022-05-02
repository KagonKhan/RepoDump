#include "stdafx.h"
#include "GameState.h"
#include "Windows.h"

#pragma region Initializer functions

//Initializer functions
void GameState::initKeybinds(){
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");	
}

void GameState::initPauseMenu(){
	this->pMenu = new PauseMenu(*this->window, this->font);
	this->pMenu->addButton("QUIT", 900.f, "Quit");
}

void GameState::initTextures() {
	if (!this->textures["IDLE"].loadFromFile("Resources/images/sprites/player/bigSheet.png"))
		throw"ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
}

void GameState::initPlayers(){
	this->player = new Player(950.f, 800.f, this->textures["IDLE"]);
}

void GameState::initBackground() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	for (int i = 1; i <= 4; i++) 
		this->bgTextures[i-1].loadFromFile("Resources/images/background/bgArena" + std::to_string(i) +".png");
	this->background.setTexture(&bgTextures[0]);
}

void GameState::initEnemy(){
	this->enemy = new Enemy(1050.f, 800.f, this->textures["IDLE"]);
}

void GameState::initStatBox(){
	this->statBox.setSize(sf::Vector2f(300.f, 280.f));
	this->statBox.setPosition(sf::Vector2f(1.f, 1.f));
	this->statBox.setFillColor(sf::Color::Black);

	this->statBox.setOutlineThickness(1.f);
	this->statBox.setOutlineColor(sf::Color::White);


	std::stringstream ss;
	ss << this->player->getHp();	
	this->statText.setString(ss.str());
	this->statText.setFont(this->font);
	this->statText.setCharacterSize(30);
	this->statText.setPosition(sf::Vector2f(1.f, 1.f));

}

void GameState::initMusic() {
	this->buffer.loadFromFile("Music/soundPageFlip.ogg");
	this->sound.setBuffer(buffer);
	this->sound.setVolume(1.f);
}

void GameState::initButtons() {

	this->buttons["ATTACK1"] = new gui::Button(
		350.f, 10.f, 200.f, 50.f,
		&this->font, "Low Attack", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
	this->buttons["ATTACK2"] = new gui::Button(
		350.f, 70.f, 200.f, 50.f,
		&this->font, "High Attack", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
	this->buttons["ATTACK3"] = new gui::Button(
		350.f, 140.f, 200.f, 50.f,
		&this->font, "Medium Attack", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["ENEMY"] = new gui::Button(
		600.f, 10.f, 200.f, 50.f,
		&this->font, "Enemy", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
	
	this->buttons["DIE"] = new gui::Button(
		1100.f, 10.f, 200.f, 50.f,
		&this->font, "Suicide", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["TOWN"] = new gui::Button(
		850.f, 10.f, 180.f, 50.f,
		&this->font, "Town", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["CHARACTER_STATE"] = new gui::Button(
		1350.f, 10.f, 180.f, 50.f,
		&this->font, "Character", 25,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["NEXT_AREA"] = new gui::Button(
		1750.f, 10.f, 100.f, 100.f,
		 "Resources/images/background/rightArrow.png",
		sf::Color(255, 255, 255, 0), sf::Color(120, 120, 120, 0), sf::Color(20, 20, 20, 0),
		sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 100),
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0)
	);

}

void GameState::initText() {
	this->missText.setFont(this->font);
	this->missText.setCharacterSize(35);
	this->missText.setFillColor(sf::Color::Red);
	this->missText.setPosition(this->player->getPosX(), this->player->getPosY());
	this->missText.setString("MISS");
	this->missText.setOutlineThickness(3.f);
	this->missText.setOutlineColor(sf::Color::Black);

}

void GameState::initVariables() {

	this->playerRound = true;
	this->timeCounter = 0.f;
	this->showMissText = false;
	this->missTextColorR = this->missTextColorG = this->missTextColorB = 0;
	this->missTextColorA = 255;
	this->missXwavePos = missYwavePos = 0.f;
}
#pragma endregion

#pragma region constructors

//Constructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states){
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPlayers();
	this->initPauseMenu();
	this->initButtons();
	this->initStatBox();
	this->initMusic();
	this->initVariables();
	this->initText();
}

GameState::~GameState(){
	delete this->player;
	delete this->pMenu;
	delete this->enemy;

	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) {
		delete it->second;
	}

	this->sound.~Sound();
}

#pragma endregion

#pragma region Update functions

//Pause / Unpause the game
void GameState::updateInput(const float& dt){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

//Player movement
void GameState::updatePlayerInput(const float& dt){}

//Pause Menu Buttons
void GameState::updatePauseMenuButtons(){
	if (this->pMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateAnimations(const float& dt) {

	if (this->player->getHp() <= 0.f) 
		if(this->player->deathAnimation(dt))
			this->states->push(new GameOverState(this->window, this->supportedKeys, this->states));
	   
	if (this->enemy && this->enemy->getHp() <= 0) {
		this->enemy->deathAnimation(dt);
		this->enemy->setWasKilled(true);
		this->playerRound = true;
	}

	if (this->enemy && this->enemy->isAnimationDone("DEATH")) {
		if (this->enemy->getWasKilled()) {
			this->player->addExp(1000);
			this->enemy->setWasKilled(false);
		}
		delete this->enemy;
		this->enemy = nullptr;
	}

	/*if (this->player->isAnimationDone("DEATH")) {
		Sleep(1000);
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states));
	}*/


	this->timeCounter += dt;
	float timeLimit = static_cast<float>(rand() % 5 + 10) / 10.f;
	if (this->enemy && this->timeCounter > timeLimit && !this->playerRound)
		this->enemyAttack(ENEMY, dt);

}

void GameState::updateText(const float& dt) {
	
	this->statText.setString(this->player->getStatistics().str());

	//Miss text updates;
	if (showMissText) {

		this->missTextColorR += 2;/*Probably remove later, for swag now*/
		this->missTextColorG += 1;
		this->missTextColorB += 0;
		this->missText.setFillColor(sf::Color(
			this->missTextColorR,
			this->missTextColorB,
			this->missTextColorG,
			this->missTextColorA));
		this->missTextColorR %= 255;
		this->missTextColorG %= 255;
		this->missTextColorB %= 255;/*========*/


		this->missXwavePos += 2.f * dt;
		this->missYwavePos += 8.f * dt;
		this->missTextColorA -= dt;
		this->missText.setPosition(sf::Vector2f(this->player->getPosX()+100.f + 10.f * cosf(missXwavePos), this->player->getPosY() - missYwavePos + 50.f));
		if (missTextColorA <= 0.f)
			this->showMissText = false;
	}

}

void GameState::update(const float& dt){
	this->updateInput(dt);
	this->updateButtons(dt);
	this->updateAnimations(dt);
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateText(dt);

	// Unpaused update
	if (!this->paused) {

		this->updatePlayerInput(dt);

		this->player->update(dt);
		if(this->enemy)
			this->enemy->update(dt);
	}
	//paused
	else {
		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::updateButtons(const float& dt) {

	if (this->playerRound) {
		for (auto it : this->buttons)
			it.second->update(this->mousePosView);
		//Attack
		if (this->buttons["ATTACK1"]->isPressed() && this->getKeytime())
			checkHit(PLAYER, 1, dt);
		if (this->buttons["ATTACK2"]->isPressed() && this->getKeytime())
			checkHit(PLAYER, 2, dt);
		if (this->buttons["ATTACK3"]->isPressed() && this->getKeytime())
			checkHit(PLAYER, 3, dt);

		//Spawn enemy
		if (this->buttons["ENEMY"]->isPressed() && this->getKeytime())
			this->initEnemy();

		if (this->buttons["DIE"]->isPressed() && this->getKeytime())
			this->player->getDamage(9999999);


		if (this->buttons["CHARACTER_STATE"]->isPressed() && this->getKeytime()) {
			this->sound.play();
			this->states->push(new CharacterScreenState(this->window, this->supportedKeys, this->states, this->player));
		}

		//Town state
		if (this->buttons["TOWN"]->isPressed() && this->getKeytime()) {
			this->enemy = nullptr;
			this->states->push(new TownState(this->window, this->supportedKeys, this->states, this->player));
		}
		if (this->buttons["NEXT_AREA"]->isPressed() && this->getKeytime()) {

			int i = rand() % 4; // change later to static loading, as this is too slow, also its not true fhd no clue why rn
			this->background.setTexture(&this->bgTextures[i]);
		}
	}
}


#pragma endregion

#pragma region Render functions

void GameState::render(sf::RenderTarget* target){

	if (!target)
		target = this->window;
	target->draw(this->background);
	this->player->render(*target);


	if(this->enemy)
		this->enemy->render(*target);


	if (this->paused) { //Pause menu render
		this->pMenu->render(*target);
	}


	if (!this->paused) {
		this->renderButtons(*target);
		target->draw(this->statBox);
		target->draw(this->statText);
	}


	if(showMissText)
		target->draw(this->missText);
}

void GameState::renderButtons(sf::RenderTarget& target) {
	if(this->playerRound)
		for (auto it : this->buttons)
			it.second->render(target);
}

#pragma endregion





void GameState::checkHit(bool type, int attackType, const float& dt) {

	if (this->enemy && this->playerRound)
		this->attack(type, attackType, dt);
	else
		this->renderMissText(dt);

}

void GameState::attack(bool type, int attackType,const float& dt) {

	this->player->setIsAttacking(attackType);

	this->enemy->getDamage(this->player->doDamage());
	this->enemy->setIsHurting();
	
	this->playerRound = false;
	this->timeCounter = 0.f;

}

void GameState::enemyAttack(bool type, const float& dt) {

	this->enemy->setIsAttacking();

	if (this->player) {
		if (type) // player=0 attacking else enemy attacking
			this->player->getDamage(this->enemy->doDamage());
	}
	
	this->playerRound = true;
	this->timeCounter = 0.f;

	this->player->setIsHurting();

}


void GameState::renderMissText(const float& dt) {
	this->showMissText = true;
	this->missTextColorA = 255;
	this->missXwavePos = 0.f;
	this->missYwavePos = 0.f;
}