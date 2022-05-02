#pragma once

#include "Tile.h"
#include "CustomShape.h"

class Game {
	sf::Clock sfClock;
	float dt;

	int n;

	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Vector2f mousePosition, dxdy;

	sf::Vector2f oldPos;

	bool isMoving;


	sf::RectangleShape boxes[3];

	int availablePieces;

	CustomShape* pieces[3];

	sf::RectangleShape gridBlock, bottomArea;
	Tile* grid[10][10];


	std::vector<int> deleteColums, deleteRows;


	bool piecesLogic[6][3][3];


	void initWindow();
	void initVariables();
	void initTiles();
	void initBackgrounds();
	void initPieces();




	void update();
	void updateSFMLevents();
	void updateDt();
	void updateKeytime();
	void updateMousePosition();
	
	
	void render();


	void movePieceOnScreen(const sf::Event& sfEvent);
	void releasePieceOnScreen();
	void spawnNewPieces();
	bool checkTaken(int n, sf::Vector2f position);

	void checkFullRowCol();

public:
	Game();
	~Game();

	void run();


};

