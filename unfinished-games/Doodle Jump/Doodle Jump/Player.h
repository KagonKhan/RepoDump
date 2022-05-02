#pragma once
#include "SFML/Graphics.hpp"
class Player {
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	sf::Vector2f velocity;

	sf::RectangleShape shape;


	float dy;
	int speed;

	bool canJump;
public:

	Player();
	int jump();

	void renderPlayer(sf::RenderWindow* window);
	sf::Vector2f getPlayerPosition();
	void update(const float& dt);

	sf::FloatRect getPlayerRectangle();
};

