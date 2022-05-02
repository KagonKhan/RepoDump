#include "Tile.h"

void Tile::coloring() {
	if (isTaken)
		shape.setFillColor(sf::Color::Green);
	else
		shape.setFillColor(sf::Color::Black);
}

Tile::Tile() {
	shape.setSize(sf::Vector2f(50.f, 50.f));

	shape.setFillColor(sf::Color::Black);

	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color::White);

	isTaken = false;

}

void Tile::changeColor(sf::Color color) {
	shape.setFillColor(color);
}

const bool Tile::getIsTaken() {
	if (isTaken)
		return true;
	return false;
}

void Tile::setIsTaken(bool isTaken) {
	this->isTaken = isTaken;
	coloring();
}

bool Tile::intersects(const sf::FloatRect& rectangle) {
	if (shape.getGlobalBounds().intersects(rectangle))
		return true;
	return false;
}

sf::Vector2f Tile::getPosition()
{
	return this->shape.getPosition();
}


void Tile::setPosition(int x, int y) { 
	shape.setPosition(x, y);
}

void Tile::render(sf::RenderWindow* target) {
	target->draw(shape);
}
