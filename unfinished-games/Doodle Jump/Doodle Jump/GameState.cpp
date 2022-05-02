#include "GameState.h"

void GameState::updateHighscore() {
	

	highscore = highscoreClock.getElapsedTime().asSeconds() * 100;
	std::cout << highscore << std::endl;
	scorestring = "score: " + std::to_string(highscore);
	highscoreText.setString(scorestring);
}

void GameState::initText() {



	font.loadFromFile("fonts/roboto.ttf");
	highscoreText.setCharacterSize(30);
	highscoreText.setFillColor(sf::Color::Black);

	highscoreText.setPosition(0, 0);

	highscoreText.setFont(font);

}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {

	srand(time(NULL));

	initText();
	initButtons();
	initBackground();
	initPlatforms();
}

GameState::~GameState() {

}



void GameState::initButtons() {
	floor.setSize(sf::Vector2f(window->getSize().x, 5.f));
	floor.setFillColor(sf::Color::Green);
	floor.setPosition(0, window->getSize().y - 5.f);
}

void GameState::initBackground() {
	bgTexture.loadFromFile("images/background.png");
	bgSprite.setTexture(bgTexture);

}

void GameState::initPlatforms() {
	for (int i = 0; i < 10; i++)
		platforms[i] = new Platform(i);
}





void GameState::update(const float& dt) {
	updateMousePos();
	updateMovement(dt);
	
	if (floor.getGlobalBounds().intersects(player.getPlayerRectangle()))
		player.jump();

	if (startHighscore) {
		updateHighscore();
	}
	else{
		highscoreClock.restart(); 
	}

	for (int i = 0; i < 10; i++)
		if (platforms[i]->getPlatformRectangle().intersects(player.getPlayerRectangle())) {

			lastJump = player.jump();

		}

	if (lastJump < 560) {
		floor.setPosition(9999, 9999);
		for (int i = 0; i < 10; i++) {
			platforms[i]->movePlatform(800);
			if (platforms[i]->getPlatformPosition().y > 570) {
				platforms[i]->setPlatformPosition(sf::Vector2f(rand() % 100 + i*50, rand()%100 - 55));
				platforms[i]->movePlatform(800);
			    startHighscore = true;
			}
		}
	}

	if (lost) {
		states->pop();
		this->states->push(new HighscoreState(this->window, this->states, highscore, true));
	}

	if (player.getPlayerPosition().y > 640) {
		lost = true;
	}

}

void GameState::updateMovement(const float& dt) {
	player.update(dt);
}



void GameState::render() {

	window->draw(bgSprite);

	for (auto it : platforms)
		it->renderPlatform(window);

	player.renderPlayer(window);
	window->draw(highscoreText);


	window->draw(floor);
}


