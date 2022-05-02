#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"
#include "Collision.h"
#include "random.h"

class World;
class Entity : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	friend class Meteor;
	friend class Player;
	friend class Saucer;
	friend class ShootPlayer;
	friend class ShootSaucer;


	sf::Sprite m_Sprite;
	sf::Vector2f m_Impulse;
	World& m_World;
	bool m_Alive;

public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	
	Entity(Configuration::Textures tex_id, World& world);
	virtual ~Entity();


	virtual bool isAlive() const;
	
	const sf::Vector2f& getPosition() const;
	template<typename ... Args>
	void setPosition(Args&& ... args);
	virtual bool isCollide(const Entity& other) const = 0;

	virtual void update(sf::Time deltaTime) = 0;
	virtual void onDestroy();
};

template<typename ...Args>
inline void Entity::setPosition(Args&& ...args)
{
	m_Sprite.setPosition(std::forward<Args>(args)...);
}
