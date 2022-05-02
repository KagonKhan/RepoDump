#pragma once
#include <SFML/Graphics.hpp>
class Action
{
	template<typename T> friend class ActionTarget;
	sf::Event m_Event;
	int m_Type;


public:
	enum Type {
		RealTime = 1,
		Pressed = 1 << 1,
		Released = 1 << 2
	};

	Action(const sf::Keyboard::Key& key, int type = Type::RealTime | Type::Pressed);
	Action(const sf::Mouse::Button& button, int type = Type::RealTime | Type::Pressed);
	Action(const Action& other);

	Action& operator=(const Action& other);

	bool test()const;

	bool operator==(const sf::Event& event) const;
	bool operator==(const Action& other) const;
	
};

