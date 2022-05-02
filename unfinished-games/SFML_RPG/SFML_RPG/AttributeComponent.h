#pragma once
class AttributeComponent
{

public:
	std::string name;

	//Leveling
	unsigned level, exp, levelExp, attributePoints;

	//Attributes
	int  vitality, strength, dexterity, agility, intelligence, luck;

	//Stats
	int hp, hpMax, damageMin, damageMax, accuracy, defence;

	//Constructors

	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions
	void gainExp(const unsigned exp);

	void updateStats(const bool reset);

	void updateLevel();

	std::string debugPrint()const;

	void update();

};

