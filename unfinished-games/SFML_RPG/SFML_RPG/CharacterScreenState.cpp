#include "stdafx.h"
#include "CharacterScreenState.h"
#include "Windows.h"

//Initializers
void CharacterScreenState::initBackgrounds() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgCharacterSheet.png")) {
		throw"ERROR::TOWNSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);



	this->frameBackground.setSize(
		sf::Vector2f(200.f,200.f));
	if (!this->frameTexture.loadFromFile("Resources/images/background/bgFrame.png")) {
		throw"ERROR::TOWNSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->frameBackground.setPosition(65.f, 75.f);
	this->frameBackground.setTexture(&frameTexture);

}

void CharacterScreenState::initVariables() {

}

void CharacterScreenState::initFonts() {
	if (this->font.loadFromFile("Fonts/Dosis-Light.otf"))
		;// throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void CharacterScreenState::initKeybinds() {}

void CharacterScreenState::initButtons() {

	this->buttons["BACK"] = new gui::Button(
		1600.f, 925.f, 250.f, 75.f,
		&this->font, "Back", 50,
		sf::Color(22, 22, 22, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	

	this->buttons["ADD_STR"] = new gui::Button(
		340.f, 400.f, 45.f, 45.f,
		&this->font, "+", 50,
		sf::Color(0, 0, 0, 255), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ADD_VIT"] = new gui::Button(
		340.f, 450.f, 45.f, 45.f,
		&this->font, "+", 50,
		sf::Color(0, 0, 0, 255), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ADD_DEX"] = new gui::Button(
		340.f, 500.f, 45.f, 45.f,
		&this->font, "+", 50,
		sf::Color(0, 0, 0, 255), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ADD_AGI"] = new gui::Button(
		340.f, 550.f, 45.f, 45.f,
		&this->font, "+", 50,
		sf::Color(0, 0, 0, 255), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ADD_INT"] = new gui::Button(
		340.f, 600.f, 45.f, 45.f,
		&this->font, "+", 50,
		sf::Color(0, 0, 0, 255), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void CharacterScreenState::initMusic() {
	this->buffer.loadFromFile("Music/soundBookClose.ogg");
	this->sound.setBuffer(buffer);
	this->sound.setVolume(100.f);
}

void CharacterScreenState::initPlayerFramePosition() {
	this->player->setPosition(
		this->frameBackground.getPosition().x + 40.f ,
		this->frameBackground.getPosition().y + 25.f
	);
}

void CharacterScreenState::initText() {
	this->nameText.setCharacterSize(110);
	this->nameText.setFont(this->font);
	this->nameText.setString(this->player->getName());
	this->nameText.setFillColor(sf::Color::Black);
	this->nameText.setPosition(sf::Vector2f(
		this->frameBackground.getPosition().x + this->frameBackground.getGlobalBounds().width + 40.f,
		this->frameBackground.getPosition().y));


	this->statText = nameText;
	this->statText.setPosition(70.f, 250.f);
	this->statText.setString(this->player->getFullStatistics().str());
	this->statText.setCharacterSize(40);
}

/*Updates buttons in the state and handles functionality*/
void CharacterScreenState::updateButtons() {


	for (auto it : this->buttons)
		it.second->update(this->mousePosView);

	//Adventure
	if (this->buttons["BACK"]->isPressed() && this->getKeytime()) {
		this->sound.play();		
		Sleep(300);
		this->endState();
	}
	if (this->buttons["ADD_STR"]->isPressed() && this->getKeytime() && this->player->attributeComponent->attributePoints > 0 ) {
		this->player->attributeComponent->strength++;
		this->player->attributeComponent->attributePoints--;
	}

	if (this->buttons["ADD_VIT"]->isPressed() && this->getKeytime() && this->player->attributeComponent->attributePoints > 0 ) {
		this->player->attributeComponent->vitality++;
		this->player->attributeComponent->attributePoints--;
	}
	if (this->buttons["ADD_DEX"]->isPressed() && this->getKeytime() && this->player->attributeComponent->attributePoints > 0 ) {
		this->player->attributeComponent->dexterity++;
		this->player->attributeComponent->attributePoints--;
	}
	if (this->buttons["ADD_AGI"]->isPressed() && this->getKeytime() && this->player->attributeComponent->attributePoints > 0)  {
		this->player->attributeComponent->agility++;
		this->player->attributeComponent->attributePoints--;
	}
	if (this->buttons["ADD_INT"]->isPressed() && this->getKeytime() && this->player->attributeComponent->attributePoints > 0 ) {
		this->player->attributeComponent->intelligence++;
		this->player->attributeComponent->attributePoints--;
	}

}

CharacterScreenState::CharacterScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Player* player)
	:State(window, supportedKeys, states), player(player) {

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initMusic();
	this->initPlayerFramePosition();
	this->initText();
}

CharacterScreenState::~CharacterScreenState() {
	this->player->setPosition(950.f, 800.f);
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) 
		delete it->second;
}

void CharacterScreenState::updateInput(const float& dt) {

}

void CharacterScreenState::update(const float& dt) {
	this->updateKeytime(dt);
	this->updateMousePositions();
	this->updateInput(dt);
	this->player->updateAnimation(dt);
	this->updateButtons();
	this->player->attributeComponent->updateStats(false);
	this->statText.setString(this->player->getFullStatistics().str());
}

void CharacterScreenState::renderButtons(sf::RenderTarget& target){
	for (auto it : this->buttons) 
		if(it.first == "BACK" || this->player->attributeComponent->attributePoints > 0 )
			it.second->render(target);
}

void CharacterScreenState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->frameBackground);
	target->draw(this->nameText);
	target->draw(this->statText);

	this->renderButtons(*target);
	this->player->render(*target);	







}
