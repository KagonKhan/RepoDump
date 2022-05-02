#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL.h>


void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	system("PAUSE");
	SDL_Quit();
	exit(420);
}