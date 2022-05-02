#include "stdafx.h"
#include "Gui.h"
#include "Windows.h"

//Button
#pragma region Button
gui::Button::Button(float x, float y, float width, float height,
				sf::Font* font, std::string text, unsigned character_size,
				sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
				sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
				sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
				short unsigned id){
	this->type = 0;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);

	float pos_x, pos_y;
		pos_x = this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f;
		pos_y = this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f;

	if(text == "+")
		pos_y = this->shape.getPosition().y - this->text.getGlobalBounds().height / 2.f;

	this->text.setPosition(pos_x, pos_y);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor   = outline_idle_color;
	this->outlineHoverColor  = outline_hover_color;
	this->outlineActiveColor = outline_active_color;



	this->id = id;
}



gui::Button::Button(float x, float y, float width, float height,
				std::string bgSource,
				sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
				sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
				sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
				short unsigned id){
	this->font = nullptr;
	this->type = 0;
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);


	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor   = outline_idle_color;
	this->outlineHoverColor  = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	
	this->texture.loadFromFile(bgSource);

	this->id = id;

	this->shape.setTexture(&texture);
	this->type = 200;
}




gui::Button::~Button(){

}


//ACCESSORS


const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const {
	return this->id;
}


//Modifiers

void gui::Button::setText(const std::string& text) {
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id) {
	this->id = id;
}

const bool gui::Button::isPressed() {
	if (this->buttonState == BTN_ACTIVE) 
		return true;
	
	return false;
}
//FUNCTIONS
void gui::Button::update(const sf::Vector2f& mousePos) {
	//IDLE
	this->buttonState = BTN_IDLE;
	//HOVER
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		//PRESSED
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}
	//COLORING
	if (this->type == 0)
		switch (this->buttonState) {
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->text.setOutlineColor(this->outlineIdleColor);
			break;
		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->text.setOutlineColor(this->outlineHoverColor);
			break;
		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			this->text.setFillColor(this->textActiveColor);
			this->text.setOutlineColor(this->outlineActiveColor);
			break;


		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->text.setOutlineColor(sf::Color::Green);
			break;

		}
}

void gui::Button::render(sf::RenderTarget& target){
	target.draw(this->shape);
	target.draw(this->text);
}

#pragma endregion



//Drop down list
#pragma region Drop Down List

gui::DropDownList::DropDownList(float x, float y, float width, float height,
								sf::Font& font, std::string listOfNames[],
								unsigned nrOfElements, const unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f){
	

	this->activeElement = new Button(
		x, y , width, height,
		&this->font, listOfNames[default_index], 14,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255),  sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200),    sf::Color(150, 150, 150, 200),  sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),    sf::Color(255, 255, 255, 255),  sf::Color(20, 20, 20, 50)
	);
	
	for (size_t i = 0; i < nrOfElements; i++) {
		this->list.push_back(
			new Button(
				x, y + ((i+1) * height) , width, height,
				&this->font, listOfNames[i], 14,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200),  sf::Color(20, 20, 20, 50),		// text color idle/hover/active
				sf::Color(70, 70, 70, 200),	   sf::Color(150, 150, 150, 200),  sf::Color(20, 20, 20, 200),		// background color idle/hover/active
				sf::Color(70, 70, 70, 0),	   sf::Color(255, 255, 255, 0),    sf::Color(20, 20, 20, 0),		// outline color idle/hover/active
				(unsigned short)i
			)
		);
	}

}

gui::DropDownList::~DropDownList() {
	delete this->activeElement;
	for (auto& i: list ) {
		delete i;
	}
}


//Accessors
const bool gui::DropDownList::getKeytime() {
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions

void gui::DropDownList::updateKeytime(const float& dt){
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt){
	
	this->updateKeytime(dt);
	//Show and hide the list 
	this->activeElement->update(mousePos);
	if (this->activeElement->isPressed() && this->getKeytime()) {
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}


	if(this->showList)
		for (auto& i : this->list) {
			i->update(mousePos);
			
			if (i->isPressed() && this->getKeytime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
}

void gui::DropDownList::render(sf::RenderTarget& target) {
	this->activeElement->render(target);

	if (this->activeElement->isPressed()) {
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
		for (auto& i : this->list)
			i->render(target);
}

























#pragma endregion

