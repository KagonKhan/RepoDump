#include "stdafx.h"
#include "Player.h"
#include "Windows.h"
//Initializer functions

void Player::initComponents(sf::Texture& texture_sheet) {
	this->createAnimationComponent(texture_sheet);
}

void Player::initAnimations() {
	this->animationComponent->addAnimation("IDLE",	  20.f, 0, 0, 12,0, 32, 32);
	this->animationComponent->addAnimation("ATTACK1", 6.f,	0, 2, 9, 2, 32, 32);
	this->animationComponent->addAnimation("ATTACK2", 10.f, 0, 3, 9, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK3", 10.f, 0, 4, 9, 4, 32, 32);
	this->animationComponent->addAnimation("HURT",	  10.f, 0, 6, 3, 6, 32, 32);
	this->animationComponent->addAnimation("DEATH",   10.f, 0, 7, 6, 7, 32, 32);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet){
	this->initComponents(texture_sheet);
	this->initAnimations();
	this->setPosition(x, y);
	this->attributeComponent->name = "Kagon";
	this->attackType = 0;
}


Player::~Player() {}

//Functions

void Player::fullHeal() {
	this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::setIsAttacking(int attackType) { 
	this->attacking = true;
	this->attackType = attackType;

};

void Player::updateAnimation(const float& dt) {

	if (this->attacking )
		switch (this->attackType) {
		case 1:
			if(this->animationComponent->play("ATTACK1", dt, true))
				this->attacking = false;
			break;
		case 2:
			if(this->animationComponent->play("ATTACK2", dt, true))
				this->attacking = false;
			break;
		case 3:
			if(this->animationComponent->play("ATTACK3", dt, true))
				this->attacking = false;
			break;
		}

	if (this->hurting) {
		this->timeCounter += dt;
		if (timeCounter > 0.15f) // slowing the start of the animation, so the flow isnt broken
			if (this->animationComponent->play("HURT", dt, true)) {
				this->hurting = false;
				this->timeCounter = 0.f;
			}
	}

	this->animationComponent->play("IDLE", dt);
}

void Player::addExp(unsigned amount) {
	this->attributeComponent->gainExp(amount);
}

void Player::update(const float& dt){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->attributeComponent->gainExp(20);
	

	this->updateHpBar();
	this->updateAnimation(dt);
}
