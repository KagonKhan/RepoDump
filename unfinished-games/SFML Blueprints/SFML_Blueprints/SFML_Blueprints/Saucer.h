#pragma once
#include "Enemy.h"
class Saucer : public Enemy
{

public:
	Saucer(const Saucer&) = delete;
	Saucer& operator=(const Saucer&) = delete;

	using Enemy::Enemy; // Use Enemy constructor

	virtual bool isCollide(const Entity& other) const;
	virtual void update(sf::Time deltaTime);
	virtual void onDestroy();

	static void newSaucer(World& world);
};

class BigSaucer : public Saucer
{
public:
	BigSaucer(World& world);
	virtual int getPoints() const;
};

class SmallSaucer : public Saucer
{
private:
	sf::Time m_TimeSinceLastShoot;

public:
	SmallSaucer(World& world);
	virtual int getPoints() const;
	virtual void update(sf::Time deltaTime);
};