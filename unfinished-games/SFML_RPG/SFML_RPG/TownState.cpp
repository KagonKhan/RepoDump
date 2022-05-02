#include "stdafx.h"
#include "TownState.h"
#include "Windows.h"

//Initializers
void TownState::initBackgrounds() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgTown.png")) {
		throw"ERROR::TOWNSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);
	
	this->buffer.loadFromFile("Music/soundSnoring.ogg");
	this->snoreSound.setBuffer(buffer);
	this->snoreSound.setVolume(1.f);
}

void TownState::initVariables() {

}

void TownState::initFonts() {
	if (this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		;// throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void TownState::initKeybinds() {}

void TownState::initButtons() {

	this->buttons["ADVENTURE"] = new gui::Button(
		850.f, 180.f, 250.f, 35.f,
		&this->font, "Adventure", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["HEAL"] = new gui::Button(
		770.f, 980.f, 250.f, 50.f,
		&this->font, "Heal", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

/*Updates buttons in the state and handles functionality*/
void TownState::updateButtons() {


	for (auto it : this->buttons)
		it.second->update(this->mousePosView);

	//Adventure
	if (this->buttons["ADVENTURE"]->isPressed()) {
		this->endState();
	}

	if (this->buttons["HEAL"]->isPressed()) {
		snoreSound.play();
		Sleep(1000);
		this->player->fullHeal();
	}
		
}

TownState::TownState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Player* player)
	:State(window, supportedKeys, states), player(player) {

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

TownState::~TownState() {
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it)
		delete it->second;
}

void TownState::updateInput(const float& dt) {

}

void TownState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void TownState::renderButtons(sf::RenderTarget& target) {
	for (auto it : this->buttons)
		it.second->render(target);
}

void TownState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

}
