#include "CustomShape.h"

CustomShape::CustomShape(bool pieceLogic[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			this->pieceLogic[j][i] = pieceLogic[j][i];
		}


	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (pieceLogic[j][i]) {
				pieceTiles[j][i] = new Tile();
				pieceTiles[j][i]->setPosition(i * 50, j * 50);
				pieceTiles[j][i]->changeColor(sf::Color::Blue);
			}
			else
				pieceTiles[j][i] = nullptr;
		}

	pieceRectangle.setSize(sf::Vector2f(3 * 50, 3 * 50));

	pieceRectangle.setFillColor(sf::Color(255, 0, 0, 100));


}

bool CustomShape::getPieceLogic(int x, int y)
{
	return pieceLogic[y][x];
}


sf::RectangleShape CustomShape::getRectangle() {
	return pieceRectangle;
}


sf::Vector2f CustomShape::getSingleSquarePosition()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (pieceLogic[j][i])
				return (pieceTiles[j][i]->getPosition() - sf::Vector2f(i*50,j*50));
}

void CustomShape::move(sf::Vector2f moveBy) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (pieceLogic[j][i])			
				pieceTiles[j][i]->setPosition(moveBy.x + i * 50, moveBy.y + j * 50);

	pieceRectangle.setPosition(moveBy);

}

bool CustomShape::snap(sf::Vector2f moveBy) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (pieceLogic[j][i]) {

				pieceTiles[j][i]->setPosition(moveBy.x + i * 50, moveBy.y + j * 50);
			}

	pieceRectangle.setPosition(moveBy);

	if(checkSnap(moveBy)) return true;
}

bool CustomShape::checkSnap(sf::Vector2f moveBy) { // FUCKING POG

	float maxY, maxX, minY, minX;
	minX = minY = 9999;
	maxX = maxY = -9999;


	// Finds the max y, x coords of the custom piece
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			if (pieceLogic[i][j]) {

				if (pieceTiles[i][j]->getPosition().x >= maxX)
					maxX = pieceTiles[i][j]->getPosition().x + 50;
			
				if (pieceTiles[i][j]->getPosition().y >= maxY)
					maxY = pieceTiles[i][j]->getPosition().y + 50;

				if (pieceTiles[i][j]->getPosition().x <= minX)
					minX = pieceTiles[i][j]->getPosition().x;

				if (pieceTiles[i][j]->getPosition().y <= minY)
					minY = pieceTiles[i][j]->getPosition().y;


			}

	

	if (maxX > 500 || maxY > 500 || minX < 0 || minY < 0) {
		move(sf::Vector2f(650, 650));
		return false;
	}

	return true;
}

void CustomShape::render(sf::RenderWindow* target) {

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (pieceLogic[j][i])
				pieceTiles[j][i]->render(target);

	target->draw(pieceRectangle);
}

