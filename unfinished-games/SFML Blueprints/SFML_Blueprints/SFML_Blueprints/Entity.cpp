#include "Entity.h"

Entity::Entity(Configuration::Textures tex_id, World& world)
	: m_World(world), m_Alive(true)
{
	sf::Texture& texture = Configuration::textures.get(tex_id);
	m_Sprite.setTexture(texture);
	m_Sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

Entity::~Entity()
{
}

bool Entity::isAlive() const
{
	return m_Alive;
}

const sf::Vector2f& Entity::getPosition() const
{
	return m_Sprite.getPosition();
}

void Entity::onDestroy()
{
	m_Alive = false;
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
