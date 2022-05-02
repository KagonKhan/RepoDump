#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
#include <vector>

class Tile {

	sf::RectangleShape shape;
	bool isTaken;


	void coloring();

public:
	Tile();

	void changeColor(sf::Color color);
	const bool getIsTaken();
	void setIsTaken(bool isTaken);
	bool intersects(const sf::FloatRect& rectangle);

	sf::Vector2f getPosition();

	void setPosition(int x, int y);
	void render(sf::RenderWindow* target);
	~Tile();
};

