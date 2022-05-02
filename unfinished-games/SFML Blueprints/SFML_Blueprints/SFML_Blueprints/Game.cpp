#include "Game.h"

#include "Configuration.h"
#include "random.h"
#include "Meteor.h"
#include "Saucer.h"
#include "Player.h"


Game::Game(int x, int y)
	: m_Window(sf::VideoMode(x, y), "GAME"),
	  m_World(x,y)
{
	m_Text.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
	m_Text.setCharacterSize(70);
	m_Text.setString("Press any key to start");

	sf::FloatRect size = m_Text.getGlobalBounds();
	m_Text.setOrigin(size.width / 2, size.height / 2);
	m_Text.setPosition(x / 2, y / 2);
}

void Game::InitLevel()
{
	int nb_meteors;
	switch (Configuration::level) {
		case 1: nb_meteors = 4; break;
		case 2: nb_meteors = 5; break;
		case 3: nb_meteors = 7; break;
		case 4: nb_meteors = 9; break;
		default:nb_meteors = 11; break;
	}
	for (int i = 0; i < nb_meteors; ++i) {
		Meteor* meteor = new BigMeteor(m_World);

		do {
			meteor->setPosition(random(0.f, (float)m_World.getX()), random(0.f, (float)m_World.getY()));
		} while (m_World.isCollide(*meteor));

		m_World.Add(meteor);
	}

}

void Game::ProcessEvents()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape))
			m_Window.close(); //close the window
	}
	
	if (Configuration::isGameOver()) {
		if (event.type == sf::Event::KeyPressed)
			Reset();
	}
	else {
		if (Configuration::player != nullptr)
			Configuration::player->ProcessEvent(event);
	}

	if (!Configuration::isGameOver() && Configuration::player != nullptr)
		Configuration::player->ProcessEvents();


}

void Game::Update(sf::Time deltaTime)
{
	m_World.Update(deltaTime);

	if (Configuration::player == nullptr) {
		Configuration::player = new Player(m_World);
		Configuration::player->setPosition(m_World.getX() / 2, m_World.getY() / 2);
		m_World.Add(Configuration::player);
	}

	m_NextSaucer -= deltaTime;

	if (m_NextSaucer < sf::Time::Zero) {
		Saucer::newSaucer(m_World);
		m_NextSaucer = sf::seconds(random(10.f, 60.f - Configuration::level * 2));
	}

	if (m_World.size() <= 1) {
		++Configuration::level;
		InitLevel();
	}

}

void Game::Reset() 
{
	m_NextSaucer = sf::seconds(random(5.f, 6.f - Configuration::level * 2));
	m_World.clear();
	Configuration::player = nullptr;
	Configuration::reset();
	InitLevel();
}
void Game::Render()
{
	m_Window.clear();

	if (Configuration::isGameOver()) {
		m_Window.draw(m_Text);
	}
	else {
		m_Window.draw(m_World);

		Configuration::draw(m_Window);
	}
	m_Window.display();
}


void Game::Run(int minFPS) 
{
	// Fixed Time steps
	/* CONSTANT TIME STEPS 
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / FPS);

	while (m_Window.isOpen()) {
		ProcessEvents();

		bool draw = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			draw = true;
			Update(TimePerFrame);
		}

		if (draw) {
			Render();
		}
	}
	*/

	// Variable Times steps
	/*sf::Clock clock;
	while (m_Window.isOpen()) {
		ProcessEvents();
		Update(clock.restart());
		Render();
	}*/

	// Mix of the 2 - min FPS, run afap

	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / minFPS);

	while (m_Window.isOpen()) {
		ProcessEvents();
		timeSinceLastUpdate = clock.restart();

		// If the game runs slower than it should
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			Update(TimePerFrame);
		}
		Update(timeSinceLastUpdate);
		Render();

	}


}


