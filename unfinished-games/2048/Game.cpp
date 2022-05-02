#include "Game.h"

Game::Game() {
	initWindow();
	initVariables();
	initTiles();
	initBackgrounds();
	initPieces();
}

Game::~Game() {

}


void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 800), "game");
}

void Game::initTiles() {
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++) {
			grid[y][x] = new Tile();
			grid[y][x]->setPosition(float(x) * 50.f, float(y) * 50.f);
		}
}

void Game::initVariables() {
	isMoving = false;
	availablePieces = 3;
}


void Game::initBackgrounds() {
	gridBlock.setSize(sf::Vector2f(505.f, 505.f));
	gridBlock.setFillColor(sf::Color::White);

	bottomArea.setSize(sf::Vector2f(window->getSize().x, window->getSize().y - gridBlock.getSize().y));
	bottomArea.setPosition(sf::Vector2f(0,gridBlock.getSize().y ));
	bottomArea.setFillColor(sf::Color::Cyan);


}

void Game::initPieces() {
	srand(time(NULL));


	for (int i = 0; i < 3; i++) {
		boxes[i].setSize(sf::Vector2f(200.f, 200.f));
		boxes[i].setPosition(50.f + (float)i * 300.f, 550.f);
		boxes[i].setFillColor(sf::Color(150, i * 500 % 255, 100 + rand() % 150));
	}


	bool piece0[3][3] = { {1,0,0},{1,0,0},{1,1,1} };
	bool piece1[3][3] = { {1,0,0},{1,0,0},{1,1,0} };
	bool piece2[3][3] = { {1,0,0},{1,0,0},{1,0,0} };
	bool piece3[3][3] = { {1,1,1},{1,1,1},{1,1,1} };
	bool piece4[3][3] = { {1,1,1},{1,0,1},{1,0,1} };
	bool piece5[3][3] = { {0,1,0},{1,1,1},{0,0,0} };


	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) {
			piecesLogic[0][y][x] = piece0[y][x];
			piecesLogic[1][y][x] = piece1[y][x];
			piecesLogic[2][y][x] = piece2[y][x];
			piecesLogic[3][y][x] = piece3[y][x];
			piecesLogic[4][y][x] = piece4[y][x];
			piecesLogic[5][y][x] = piece5[y][x];

		}


	pieces[0] = new CustomShape(piecesLogic[rand()%6]);
	pieces[1] = new CustomShape(piecesLogic[rand()%6]);
	pieces[2] = new CustomShape(piecesLogic[rand()%6]);
	
	

	pieces[0]->move(boxes[0].getPosition());
	pieces[1]->move(boxes[1].getPosition());
	pieces[2]->move(boxes[2].getPosition());
	
}

void Game::update() {
	updateSFMLevents();
	updateDt();
	updateMousePosition();
}

void Game::updateSFMLevents() {

	while (window->pollEvent(sfEvent)) {
		if (sfEvent.type == sf::Event::Closed)
			window->close();

		if (sfEvent.type == sf::Event::MouseButtonPressed && sfEvent.key.code == sf::Mouse::Left)
			movePieceOnScreen(sfEvent);

		if (sfEvent.type == sf::Event::MouseButtonReleased && sfEvent.key.code == sf::Mouse::Left)
			releasePieceOnScreen();

	}

	if (!availablePieces)
		spawnNewPieces();


	if (isMoving)
		pieces[n]->move(mousePosition - dxdy);

}

void Game::updateDt() {

}

void Game::updateKeytime() {

}

void Game::updateMousePosition() {
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}


void Game::render() {
	window->clear();


	window->draw(gridBlock);


	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			if(grid[y][x])
				grid[y][x]->render(window);
	

	window->draw(bottomArea);

	for (int i = 0; i < 3; i++)
		window->draw(boxes[i]);
	
	for(int i = 0; i < 3; i++)
		if(pieces[i])
			pieces[i]->render(window);

	window->display();
}

void Game::		(const sf::Event& sfEvent) {
	for (int i = 0; i < 3; i++)
		if (pieces[i])
			if (pieces[i]->getRectangle().getGlobalBounds().contains(mousePosition)) {
				n = i;
				isMoving = true;
				dxdy = sf::Vector2f(mousePosition.x - pieces[i]->getRectangle().getPosition().x, mousePosition.y - pieces[i]->getRectangle().getPosition().y);
			}


}

void Game::releasePieceOnScreen()
{
	if (pieces[n]) {
		isMoving = false;

		sf::Vector2f pos = pieces[n]->getSingleSquarePosition();
		sf::Vector2f pos2(pos.x + 25, pos.y + 25);
		sf::Vector2f pos3(int(pos2.x) / 50, int(pos2.y) / 50);
		sf::Vector2f pos4(pos3.x * 50, pos3.y * 50);

		if (pieces[n]->snap(pos4)) {
			if (checkTaken(n, pos3)) {
				for (int y = 0; y < 3; y++)
					for (int x = 0; x < 3; x++)
						if (pieces[n]->getPieceLogic(x, y))
							grid[int(pos3.y + y)][int(pos3.x + x)]->setIsTaken(true);;;
				delete pieces[n];
				pieces[n] = nullptr;

				checkFullRowCol();

				availablePieces--;
			}
			else
				pieces[n]->move(boxes[n].getPosition());
		}
		else
			pieces[n]->move(boxes[n].getPosition());
	}
}

void Game::spawnNewPieces() {

	srand(time(NULL));

	pieces[0] = new CustomShape(piecesLogic[rand() % 6]);

	for (int i = 0; i < 10000; i++);

	pieces[1] = new CustomShape(piecesLogic[rand() % 6]);

	for (int i = 0; i < 10000; i++);

	pieces[2] = new CustomShape(piecesLogic[rand() % 6]);
	


	pieces[0]->move(boxes[0].getPosition());
	pieces[1]->move(boxes[1].getPosition());
	pieces[2]->move(boxes[2].getPosition());

	
	availablePieces = 3;
}

bool Game::checkTaken(int n, sf::Vector2f position)
{
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			if (pieces[n]->getPieceLogic(x, y))
				if (grid[int(position.y + y)][int(position.x + x)]->getIsTaken())
					return false;


	return true;
}






void Game::checkFullRowCol() {

	deleteColums.clear();
	deleteRows.clear();

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (!grid[y][x]->getIsTaken())
				break;
			if (x == 9)
				deleteRows.push_back(y);
		}
	}

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (!grid[x][y]->getIsTaken())
				break;
			if (x == 9)
				deleteColums.push_back(y);
		}
	}

	system("CLS");


	for (auto x : deleteRows) {
		for (int y = 0; y < 10; y++)
			grid[x][y]->setIsTaken(false);
	}

	for (auto x : deleteColums) {
		for (int y = 0; y < 10; y++)
			grid[y][x]->setIsTaken(false);
	}


}









void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}
}
