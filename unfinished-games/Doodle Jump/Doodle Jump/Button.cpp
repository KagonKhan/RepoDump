#include "Button.h"

Button::Button(sf::Vector2f position, sf::Color color) {

	shape.setSize(sf::Vector2f(150,100));
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color::Black);
	buttonState = buttonIdle;

}

Button::~Button() {

}

void Button::render(sf::RenderWindow* window) {

	window->draw(shape);
}

bool Button::isButtonPressed() {

	if (buttonState == buttonActive)
		return true;
	return false;
}

void Button::update(const sf::Vector2f &mousePosition) {

	buttonState = buttonIdle;

	if (shape.getGlobalBounds().contains(mousePosition)) 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			buttonState = buttonActive;
	
}
