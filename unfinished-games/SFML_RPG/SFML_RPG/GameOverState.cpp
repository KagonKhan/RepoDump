#include "stdafx.h"
#include "GameOverState.h"

//Initializers
void GameOverState::initBackgrounds() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgEnd.png")) {
		throw"ERROR::TOWNSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);

}

void GameOverState::initVariables() {

}

void GameOverState::initFonts() {
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		throw("ERROR::GAMEOVERSTATE::COULD NOT LOAD FONT");
}

void GameOverState::initKeybinds() {}

void GameOverState::initText() {
	this->gameOverText.setCharacterSize(180);
	this->gameOverText.setFont(this->font);
	this->gameOverText.setString(std::string("GAME OVER"));
	this->gameOverText.setOutlineThickness(1.f);
	this->gameOverText.setOutlineColor(sf::Color::Red);
	this->gameOverText.setPosition(sf::Vector2f(this->window->getSize().x/2.f - 400.f, 200.f));
}

void GameOverState::initButtons() {

	this->buttons["BACK"] = new gui::Button(
		this->window->getSize().x / 2.f - 125.f, 900.f, 250.f, 50.f,
		&this->font, "Main Menu", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void GameOverState::updateButtons() {

	for (auto it : this->buttons)
		it.second->update(this->mousePosView);

	//Adventure
	if (this->buttons["BACK"]->isPressed()) {
		this->states->pop();
		this->states->pop();
	}
	
}

GameOverState::GameOverState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states), player(player) {

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initText();
}

GameOverState::~GameOverState() {
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) {
		delete it->second;
	}
}

void GameOverState::updateInput(const float& dt) {

}

void GameOverState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();



}

void GameOverState::renderButtons(sf::RenderTarget& target) {
	for (auto it : this->buttons)
		it.second->render(target);

}

void GameOverState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	target->draw(gameOverText);
}
