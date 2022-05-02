#include "Player.h"
#include <iostream>


Player::Player() {
	playerTexture.loadFromFile("images/PlayerBody.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(sf::Vector2f(400, 520));
	speed = 200;

	canJump = true;
	playerSprite.setOrigin(20.f,20.f);
	velocity.y = -2000;
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color(255, 0, 0, 100));
	shape.setPosition(playerSprite.getPosition());

}




sf::Vector2f Player::getPlayerPosition() {
	return playerSprite.getPosition();
}


void Player::update(const float& dt) {

	shape.setPosition(playerSprite.getPosition());



	velocity.x *=0.8;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && playerSprite.getPosition().x > 0)
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && playerSprite.getPosition().x < 730)
		velocity.x += speed;

	if (velocity.x > 0) {
		//playerSprite.setScale(-1.f, 1.f);
	}

	if (velocity.x < 0) {
		playerSprite.setScale(1.f, 1.f);
	}

	velocity.y += 50.f;



	playerSprite.move(velocity * dt);

}

sf::FloatRect Player::getPlayerRectangle() {
	return playerSprite.getGlobalBounds();
}

int Player::jump() {
	if (velocity.y > 0) {//moving down
		velocity.y = -2000;
		return playerSprite.getPosition().y;
	}
	return 9999;
}


void Player::renderPlayer(sf::RenderWindow* window) {
	window->draw(playerSprite);
	window->draw(shape);
}
