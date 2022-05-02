#pragma once
#include "SFML/Graphics.hpp"
#include "ActionTarget.h"
#include "Configuration.h"
#include "Entity.h"

class Player : public Entity, public ActionTarget<int>
{
private:
	bool m_IsMoving;
	int m_Rotation;
	sf::Time m_TimeSinceLastShoot;

public:
	Player(const Player&) = delete;
	Player& operator==(const Player&) = delete;

	Player(World& world);

	virtual bool isCollide(const Entity& other) const;
	virtual void update(sf::Time deltaTime);
	
	void ProcessEvents();

	void Shoot();

	void Jump();

	virtual void onDestroy();

};

