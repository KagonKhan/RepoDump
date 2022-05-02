#pragma once
#include "SFML/Graphics.hpp"
class Platform {
	sf::Sprite platformSprite;
	sf::Texture platformTexture;

	sf::RectangleShape shape;
	float moveBy;
public:
	Platform(int x);
	void renderPlatform(sf::RenderTarget* window);
	sf::FloatRect getPlatformRectangle();
	void movePlatform(float y);
	sf::Vector2f getPlatformPosition();
	void setPlatformPosition(sf::Vector2f pos);
};

