#include "stdafx.h"
#include "MainMenuState.h"

//Initializers
void MainMenuState::initBackgrounds(){
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgBegin.png")) {
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);

}

void MainMenuState::initVariables(){

}

void MainMenuState::initFonts(){
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf")) 
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void MainMenuState::initKeybinds() {

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}

void MainMenuState::initMusic() {
	if (!this->bgMusic.openFromFile("Music/bgMusic.ogg"))
		throw "MUSIC NOT OPEN";
	
	this->bgMusic.setLoop(true);
	this->bgMusic.setVolume(1.f);
	this->bgMusic.play();

}

void MainMenuState::initButtons(){

	this->buttons["GAME_STATE"] =		new gui::Button(50.f, 480.f, 250.f, 50.f,
		&this->font, "New Game", 50,
		sf::Color(255, 255, 255, 200),	sf::Color(120, 120, 120, 250),	sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),		sf::Color(150, 150, 150, 0),	sf::Color(20, 20, 20, 0 ));
	
	this->buttons["SETTINGS_STATE"] =	new gui::Button(50.f, 580.f, 250.f, 50.f,
		&this->font, "Settings", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),	sf::Color(150, 150, 150, 0),	sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] =		new gui::Button(50.f, 780.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),	sf::Color(150, 150, 150, 0),	sf::Color(20, 20, 20, 0));


}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states) {

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initMusic();

} 


MainMenuState::~MainMenuState(){
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it)
		delete it->second;
}


void MainMenuState::updateInput(const float& dt) {
	
}

void MainMenuState::updateButtons(){

	/*Updates buttons in the state and handles functionality*/

	for (auto it : this->buttons) 
		it.second->update(this->mousePosView);
	
	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));

	//Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
		this->endState();
	

}

void MainMenuState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

	

}

void MainMenuState::renderButtons(sf::RenderTarget& target){
	for (auto it : this->buttons) 
		it.second->render(target);
	
}

void MainMenuState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target); 

}
