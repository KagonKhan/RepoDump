#include "stdafx.h"
#include "AttributeComponent.h"
//Constructors

AttributeComponent::AttributeComponent(unsigned level) {
	this->level = level;
	this->exp = 0;
	this->levelExp = 20;
	this->attributePoints = 7;
	this->name = "Unknown";

	this->vitality = this->strength = this->dexterity = this->agility = this->luck = this->intelligence = 1;
	
	this->updateLevel();

	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}


void AttributeComponent::gainExp(const unsigned exp) {
	this->exp += exp;
	this->updateLevel();
}

//Functions
void AttributeComponent::updateStats(const bool reset) {
	this->hpMax = this->vitality * 10 + this->level * 50 + this->strength * 3;
	if(reset)
		this->hp = this->hpMax;

	this->damageMax	= this->strength	 * 5;
	this->damageMin	= this->strength	 * 2;
	this->accuracy	= this->dexterity	 * 3;
	this->defence	= this->agility		 * 3;
	this->luck		= this->intelligence * 2;
}

void AttributeComponent::updateLevel() {	
	while (this->exp >= this->levelExp) {
		this->exp -= levelExp;
		++this->level;
		this->levelExp = static_cast<unsigned>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		this->attributePoints += 3;
	}
	this->updateStats(true);
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;
	ss << "\tName: " << this->name <<

		"\n\t\tHp: " << this->hp << "/" << this->hpMax <<
		"\n\t\tStrength: " << this->strength <<
		"\n\t\tEndurance: " << this->vitality <<
		"\n\t\tAgility: " << this->agility <<
		"\n\t\tAttPoints: " << this->attributePoints <<
		"\n\t\tLevel: " << this->level <<
		"\n\t\texp: " << this->exp << "/" << this->levelExp;


	return ss.str();
}

void AttributeComponent::update() {
	this->updateLevel();
}
