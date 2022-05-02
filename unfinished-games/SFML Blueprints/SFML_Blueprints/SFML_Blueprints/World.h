#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <list>
#include <memory>

#include "Configuration.h"

class Entity;
class World : public sf::Drawable
{
	std::list<Entity*> m_Entities;
	std::list<Entity*> m_Entities_tmp;
	std::list<std::unique_ptr<sf::Sound>> m_Sounds;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const int m_SizeX, m_SizeY;

public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	
	World(float x, float y);
	~World();

	void Add(Entity* entity);
	void Add(Configuration::Sounds sound_id);
	
	void clear();
	int size();
	int getX()const;
	int getY()const;
	
	bool isCollide(const Entity& other);
	const std::list<Entity*> getEntities()const;

	void Update(sf::Time deltaTime);
};

