
#include "Game.h"

int main() {
	Game game;
	game.run();
	






















	/*
	float h = 200; //variable used to scroll the map
	srand(time(NULL));
	//Loading textures
	Texture PlayerBody,Background,PlatformTexture;
	PlayerBody.loadFromFile("images/PlayerBody.png");
	Background.loadFromFile("images/background.png");
	PlatformTexture.loadFromFile("images/platform.png");
	Texture *PlayerBodyPointer = &PlayerBody;
	Texture* PlatformPointer = &PlatformTexture;

	//Creating Background
	Sprite GameBackground(Background);
	//Creating Platforms
	Platform platforms[20];
	for (int i = 0; i < 10; i++) {
		platforms[i].setPlatform(PlatformPointer,i);
	}

	//Creating Player
	Player player1(PlayerBodyPointer);
	RenderWindow window(VideoMode(800, 600), "Doodle Jump");
	Event event;
	window.setFramerateLimit(144);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(GameBackground);//Drawing Background
		window.draw(player1.showBody());//Drawing player character
		player1.PlayerMovement();//Turning on physics associated with player body
		if (player1.getPosY() < h)
			for (int i = 0; i < 10; i++) {
				player1.setPositionY(h);
				platforms[i].setPositionY((platforms[i].getPosY() - player1.getDy()));
				if (platforms[i].getPosY() > 500) {
					platforms[i].setPositionY(0);
					platforms[i].setPositionX(rand() % 400);
				}
			}
		for (int i = 0; i < 10; i++) {
			if ((player1.getPosX() + 50 >= platforms[i].getPosX())
				&& (player1.getPosX() + 20 < platforms[i].getPosX() + 68)
				&& (player1.getPosY() + 70 >= platforms[i].getPosY())
				&& (player1.getPosY() + 70 < platforms[i].getPosY() + 14)
				&& (player1.getDy() > 0))
				player1.setDy();
		}
		for (int i = 0; i < 10; i++) {//Loop responsible for drawing platforms
			window.draw(platforms[i].showBody());
		}
		window.display();
	}*/

	return 0;
}