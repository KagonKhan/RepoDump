#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
				: State(window, supportedKeys, states){

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState() {
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it) 
		delete it->second;

	for (auto it = this->dropDownLists.begin(); it != dropDownLists.end(); ++it)
		delete it->second;
	
}

//Initializers
void SettingsState::initBackgrounds() {
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/images/background/bgLake.png")) {
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&backgroundTexture);

}
void SettingsState::initVariables() {

}
void SettingsState::initFonts() {
	if (this->font.loadFromFile("Fonts/Dosis-Light.otf")) {
		//	throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}

}
void SettingsState::initKeybinds() {

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}
void SettingsState::initGui() {

	this->buttons["BACK"] = new gui::Button(
		this->window->getSize().x / 2.f, 780.f, 250.f, 50.f,
		&this->font, "Back", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	
	this->buttons["APPLY"] = new gui::Button(
		this->window->getSize().x / 2.f - 250.f, 780.f, 250.f, 50.f,
		&this->font, "Apply", 50,
		sf::Color(255, 255, 255, 200), sf::Color(120, 120, 120, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string resolutions[] = { "1920x1080","800x600","640x480"};

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(this->window->getSize().x / 2.f - 100.f, 400, 200, 50, font, resolutions, 3);

}



//Functions
void SettingsState::updateInput(const float& dt) {

}

void SettingsState::updateGui(const float& dt) {

	/*Updates gui in the state and handles functionality*/
	//Buttons
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);


	//Quit game
	if (this->buttons["BACK"]->isPressed())
		this->endState();

	//Apply changes
	if (this->buttons["APPLY"]->isPressed())
		this->endState();


	//Drop down lists 
	for (auto& it : this->dropDownLists)
		it.second->update(this->mousePosView, dt);


}

void SettingsState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui(dt);



}

void SettingsState::renderGui(sf::RenderTarget& target) {
	
	//Buttons
	for (auto it : this->buttons)
		it.second->render(target);

	//Lists
	for (auto it : this->dropDownLists)
		it.second->render(target);

}

void SettingsState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);


}
