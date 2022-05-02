#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"



class Button {

	enum ButtonStates {
		buttonIdle = 0, buttonActive
	};



	sf::RectangleShape shape;
	short unsigned buttonState;

public:
	Button(sf::Vector2f position, sf::Color color);
	~Button();



	void update(const sf::Vector2f& mouse_position);

	void render(sf::RenderWindow *window);



	bool isButtonPressed();



};

