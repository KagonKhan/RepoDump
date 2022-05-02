#pragma once

#include "AnimationComponent.h"
#include "AttributeComponent.h"

class Entity{
private:
	virtual void initVariables();
	virtual void initHpBars();


protected:
	virtual void updateHpBar();
	bool attacking, hurting;
	sf::Sprite sprite;
	AnimationComponent* animationComponent;

	sf::Font font;
	sf::Text deathText;
	sf::Text missText;
	sf::RectangleShape hpBarMax;
	sf::RectangleShape hpBar;
	float hpRatio;

	/*Entity variables*/


public:

	AttributeComponent* attributeComponent;
	virtual bool deathAnimation(const float& dt);

	Entity();
	virtual ~Entity();

	//Component functions
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);
	void setTexture(sf::Texture& texture);

	virtual std::string getName() { return this->attributeComponent->name; };

	//Functions
	virtual int doDamage();
	void getDamage(int damage);
	virtual void setIsAttacking() { this->attacking = true; };
	void setIsHurting() { this->hurting = true; };
	bool getIsAttacking() { return this->attacking; };
	double getHp();

	virtual void setPosition(const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);


	


	float timeCounter;

	std::stringstream getStatistics();
	std::stringstream getFullStatistics();
};


