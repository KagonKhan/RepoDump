#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>

#include "Shoot.h"


Player::Player(World& world) 
	: Entity(Configuration::Textures::Player, world),
	  ActionTarget(Configuration::playerInputs),
	  m_IsMoving(false),
	  m_Rotation(0)
{

	Bind(Configuration::PlayerInputs::Up,			[this](const sf::Event&) {m_IsMoving = true; });
	Bind(Configuration::PlayerInputs::Left,			[this](const sf::Event&) {m_Rotation -= 1; });
	Bind(Configuration::PlayerInputs::Right,		[this](const sf::Event&) {m_Rotation += 1; });
	Bind(Configuration::PlayerInputs::Shoot,		[this](const sf::Event&) {Shoot(); });
	Bind(Configuration::PlayerInputs::Hyperspace,	[this](const sf::Event&) {Jump(); });

}

bool Player::isCollide(const Entity& other) const
{
	if (dynamic_cast<const ShootPlayer*>(&other) == nullptr) 
		return Collision::circleTest(m_Sprite, other.m_Sprite);
	
	return false;
}

void Player::ProcessEvents()
{
	m_IsMoving = false;
	m_Rotation = 0;
	ActionTarget::ProcessEvents();
}

void Player::Shoot()
{
	if (m_TimeSinceLastShoot > sf::seconds(0.3)) {
		m_World.Add(new ShootPlayer(*this));
		m_TimeSinceLastShoot = sf::Time::Zero;
	}
}

void Player::Jump()
{
	m_Impulse = sf::Vector2f(0, 0);
	setPosition(random(0, m_World.getX()), random(0, m_World.getY()));
	m_World.Add(Configuration::Sounds::Jump);
}

void Player::onDestroy()
{
	Entity::onDestroy();
	Configuration::player = nullptr;

	Configuration::lives--;
	m_World.Add(Configuration::Sounds::Boom1);
}


void Player::update(sf::Time deltaTime) {
	float seconds = deltaTime.asSeconds();
	m_TimeSinceLastShoot += deltaTime;

	if (m_Rotation != 0) {
		float angle = m_Rotation* 180 * seconds;
		m_Sprite.rotate(angle);
	}
	if (m_IsMoving) {
		double angle = m_Sprite.getRotation() / 180 * M_PI - M_PI / 2;
		m_Impulse += sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds;
	}
	m_Sprite.move(seconds * m_Impulse);
}

