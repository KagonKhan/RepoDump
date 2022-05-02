#pragma once

#include "Entity.h"

class Player :	public Entity{
private:

	//Variables

	int attackType;
	//Initializer functions
	void initComponents(sf::Texture& texture_sheet);
	void initAnimations();

public:
	//constructors
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	virtual void update(const float& dt);
	virtual void updateAnimation(const float& dt);
	virtual void setIsAttacking(int attackType);

	float getPosX() { return this->hpBarMax.getPosition().x; }
	float getPosY() { return this->hpBarMax.getPosition().y; }

	void fullHeal();

	bool isAnimationDone(std::string key) { return this->animationComponent->isDone(key); };
	void addExp(unsigned amount);
};

