#include "Game.h"
#include <iostream>
#include "Configuration.h"


int main(int argc, char* argv[]) {

	Configuration::initialize();

	Game game;
	game.Run(75);
	return 0;
}