#define _USE_MATH_DEFINES
#include "Shoot.h"

#include "Collision.h" //Collision
#include "Enemy.h" //Enemy
#include "Player.h" //Player
#include "Saucer.h" //Saucer
#include "Meteor.h" //Meteor
#include "World.h" //World


void Shoot::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();

	m_Sprite.move(seconds * m_Impulse);
	m_Duration -= deltaTime;

	if (m_Duration < sf::Time::Zero)
		m_Alive = false;
}


ShootPlayer::ShootPlayer(Player& from)
	: Shoot(Configuration::Textures::ShootPlayer, from.m_World)
{
	m_Duration = sf::seconds(5);

	float angle = from.m_Sprite.getRotation() / 180 * M_PI - M_PI / 2;
	m_Impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;
	setPosition(from.getPosition());

	m_Sprite.setRotation(from.m_Sprite.getRotation());

	m_World.Add(Configuration::Sounds::LaserPlayer);


}



bool ShootPlayer::isCollide(const Entity& other) const
{
	if (dynamic_cast<const Enemy*>(&other) != nullptr)
		return Collision::circleTest(m_Sprite, other.m_Sprite);
	return false;
}



ShootSaucer::ShootSaucer(SmallSaucer& from)
	: Shoot(Configuration::Textures::ShootSaucer, from.m_World)
{
	m_Duration = sf::seconds(5);


	sf::Vector2f pos = Configuration::player->getPosition() - from.getPosition();

	float accuracy_lost = random(-1.f, 1.f) * M_PI / ((200 + Configuration::getScore()) / 100.f);
	float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
	float angle_deg = angle_rad * 180 / M_PI;

	m_Impulse = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;

	setPosition(from.getPosition());
	m_Sprite.setRotation(angle_deg + 90);
	m_World.Add(Configuration::Sounds::LaserEnemy);
}


bool ShootSaucer::isCollide(const Entity& other)const
{
	if (dynamic_cast<const Player*>(&other) || dynamic_cast<const Meteor*>(&other))
	{
		return Collision::circleTest(m_Sprite, other.m_Sprite);
	}
	return false;
}
