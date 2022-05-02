#include "TextButton.h"
#include "VerticalLayout.h"
#include "TableLayout.h"
#include "UnorderedLayout.h"
#include "UserInterface.h"
#include "HorizontalLayout.h"
#include "CheckboxButton.h"
#include <cmath>
#include "SpriteButton.h"
#include "ResourceManager.h"
/* so far seems like there are no memory leaks */


#include "ArrowSwitchTextButton.h"









enum class Fonts {
	Chopsic
};

enum class Textures {
	button,
	left_arrow,
	right_arrow
};

ResourceManager<sf::Texture, Textures> m_Textures;
ResourceManager<sf::Font, Fonts> m_Fonts;

int main() {

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "End me");
	sf::Event sfevent;


	m_Fonts.load(Fonts::Chopsic, "font/Chopsic.ttf");
	m_Textures.load(Textures::button, "../media/button_test.png");
	m_Textures.load(Textures::left_arrow, "../media/left_arrow.png");
	m_Textures.load(Textures::right_arrow, "../media/right_arrow.png");


	
	std::unique_ptr<ArrowSwitchTextButton> testing(
		new ArrowSwitchTextButton{ std::nullopt, sf::Vector2f (1100, 75),
			"TESTING", m_Fonts.get(Fonts::Chopsic), 40,
			8, sf::Vector2f(300, 75), m_Textures.get(Textures::left_arrow) , m_Textures.get(Textures::right_arrow), sf::Vector2f(50,35)}
	);
	testing->addOption("1920 x 1080", m_Fonts.get(Fonts::Chopsic), 20);
	testing->addOption("test 1", m_Fonts.get(Fonts::Chopsic), 20);
	testing->addOption("test 2", m_Fonts.get(Fonts::Chopsic), 20);

	std::unique_ptr<VerticalLayout> layout = std::make_unique<VerticalLayout>(2, std::nullopt);
	layout->add(std::move(testing));

	UserInterface ui;
	ui.addLayout(std::move(layout));
	ui.setPositionAtIndex(500, 500, 0);


	while (window.isOpen()) {
		while (window.pollEvent(sfevent)) {
			if (sfevent.type == sf::Event::Closed)
				window.close();
			

			ui.processEvent(sfevent);
		
		}

		window.clear();

		window.draw(ui);
		window.display();
	}

}