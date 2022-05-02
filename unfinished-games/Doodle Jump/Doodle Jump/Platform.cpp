#include "Platform.h"



Platform::Platform(int x) {
	platformTexture.loadFromFile("images/platform.png");
	platformSprite.setTexture(platformTexture);
	platformSprite.setPosition(25 + (rand() % 600), 55 * (x + 1));
	shape.setSize(sf::Vector2f(50, 10));
	shape.setFillColor(sf::Color(255, 0, 0, 100));
	sf::Vector2f shapePos(platformSprite.getPosition());
	moveBy = 0;
	shapePos.x += 7.f;

	shape.setPosition(shapePos);
}

void Platform::renderPlatform(sf::RenderTarget* window) {
	window->draw(platformSprite);
	window->draw(shape);

	if (moveBy > 0) {
		platformSprite.move(0, 3);
		shape.move(0, 3);
		moveBy -= 2;
	}

}

sf::FloatRect Platform::getPlatformRectangle() {
	return shape.getGlobalBounds();
}

void Platform::movePlatform(float y) {

	moveBy = y;
}

sf::Vector2f Platform::getPlatformPosition()
{
	return platformSprite.getPosition();
}

void Platform::setPlatformPosition(sf::Vector2f pos) {
	platformSprite.setPosition(pos);
	shape.setPosition(pos);
}
