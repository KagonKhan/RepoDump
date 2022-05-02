#pragma once
#include "SFML/Graphics.hpp"
#include "Tile.h"


class CustomShape {
	bool pieceLogic[3][3];
	sf::RectangleShape pieceRectangle;
	Tile* pieceTiles[3][3];


	bool checkSnap(sf::Vector2f moveBy);

public:
	CustomShape(bool pieceLogic[3][3]);

	sf::RectangleShape getRectangle();
	sf::Vector2f getSingleSquarePosition();

	bool snap(sf::Vector2f moveBy);
	void move(sf::Vector2f moveBy);

	bool getPieceLogic(int x, int y);

	void render(sf::RenderWindow* target);
};

