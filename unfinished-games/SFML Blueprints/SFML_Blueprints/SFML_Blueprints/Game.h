#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "World.h"

class Game {
	sf::RenderWindow m_Window;
	World m_World;

	sf::Time m_NextSaucer;
	sf::Text m_Text;

	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	void Reset();

public:
	Game(const Game&) = delete;
	Game& operator ==(const Game&) = delete;

	Game(int x = 1600, int y = 900);
	void Run(int FPS = 30);

	void InitLevel();
};


