#include "HighscoreState.h"
#include <sstream>
#include <fstream>

void HighscoreState::initBackground() {
	backgroundShape.setSize(sf::Vector2f(800,600));
	backgroundShape.setFillColor(sf::Color::Yellow);

	middleShape.setSize(sf::Vector2f(300, 800));
	middleShape.setPosition((window->getSize().x - middleShape.getSize().x )/ 2, 0);
	middleShape.setFillColor(sf::Color::White);
	font.loadFromFile("fonts/roboto.ttf");

	highscoreText.setCharacterSize(30);
	highscoreText.setFillColor(sf::Color::Black);
	highscoreText.setPosition(middleShape.getPosition().x, 0);
	highscoreText.setFont(font);


}

void HighscoreState::updateText(int score) {
	std::string test = "";
	std::string result = "";
	if (1) {
		std::ifstream file("fonts/highscores.txt");
		if (file.is_open()) 		{
			while (std::getline(file, test))
				result += test + "\n";
			file.close();
		}
		//std::cout << test;
		file.close();

	}
	highscoreText.setString(result);



	sf::Vector2f(window->getSize().x - 125.f / 2.f, window->getSize().y - 75.f);



}

HighscoreState::HighscoreState(sf::RenderWindow* window, std::stack<State*>* states, int score, bool write) : State(window,states){
	initBackground();
	system("CLS");

	if (write && score) {
		std::ofstream file("fonts/highscores.txt", std::ios_base::app);
		file << std::to_string(score )+  "\n";
		std::cout << std::to_string(score) + "\n";
		file.close();
	}
	updateText(score);

}

void HighscoreState::update(const float& dt) {
	int a;
}

void HighscoreState::render() {
	window->draw(backgroundShape);
	window->draw(middleShape);
	window->draw(highscoreText);
}
