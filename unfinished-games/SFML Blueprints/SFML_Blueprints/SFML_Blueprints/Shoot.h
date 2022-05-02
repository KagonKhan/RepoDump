#pragma once
#include "Entity.h"

class Shoot : public Entity
{
protected:
	sf::Time m_Duration;

public:
	Shoot(const Shoot&) = delete;
	Shoot& operator=(const Shoot&) = delete;

	using Entity::Entity;

	virtual void update(sf::Time deltaTime);
};

class ShootPlayer : public Shoot
{
public:
	ShootPlayer(const ShootPlayer&) = delete;
	ShootPlayer& operator=(const ShootPlayer&) = delete;

	ShootPlayer(Player& from);

	virtual bool isCollide(const Entity& other) const;

};

class SmallSaucer;
class ShootSaucer : public Shoot
{
public:
	ShootSaucer(const ShootSaucer&) = delete;
	ShootSaucer& operator=(const ShootSaucer&) = delete;

	ShootSaucer(SmallSaucer& from);

	virtual bool isCollide(const Entity& other) const;

};



