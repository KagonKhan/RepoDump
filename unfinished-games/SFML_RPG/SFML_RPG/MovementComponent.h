#pragma once


enum movement_states {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent{
private:

	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	//Initializers


protected:

public:
	//Constructors
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;



	//functions
	const bool getState(const short unsigned state) const;
	const bool moving() const;


	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);


};

