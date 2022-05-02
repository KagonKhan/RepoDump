#include "World.h"
#include "Entity.h"

World::World(float x, float y)
	: m_SizeX(x), m_SizeY(y)
{
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Entity* entity : m_Entities)
		target.draw(*entity, states);
}



World::~World()
{
	clear();
}

void World::Add(Entity* entity)
{
	m_Entities_tmp.emplace_back(entity);
}

void World::clear()
{
	for (Entity* entity : m_Entities)
		delete entity;
	m_Entities.clear();
	
	for (Entity* entity : m_Entities_tmp)
		delete entity;
	m_Entities_tmp.clear();

	m_Sounds.clear();
}

bool World::isCollide(const Entity& other)
{
	for (Entity* entity_ptr : m_Entities)
		if (other.isCollide(*entity_ptr))
			return true;
	return false;
}

int World::size()
{
	return m_Entities.size() + m_Entities_tmp.size();
}

void World::Add(Configuration::Sounds sound_id)
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));
	sound->setAttenuation(0);
	sound->play();
	m_Sounds.emplace_back(std::move(sound));
}

const std::list<Entity*> World::getEntities() const
{
	return m_Entities;
}

int World::getX() const
{
	return m_SizeX;
}

int World::getY() const
{
	return m_SizeY;
}

void World::Update(sf::Time deltaTime)
{
	//TODO: throws exceptions
	if (m_Entities_tmp.size() > 0)
		m_Entities.splice(m_Entities.end(), m_Entities_tmp);

	for (Entity* entity_ptr : m_Entities) {
		Entity& entity = *entity_ptr; // is there a point to this? Entity*&?

		entity.update(deltaTime);

		sf::Vector2f pos = entity.getPosition();

		if (pos.x < 0) {
			pos.x = m_SizeX;
			//player_pos.y = m_SizeY - player_pos.y; // necessary?
		}
		else if (pos.x > m_SizeX) {
			pos.x = 0;
			//player_pos.y = m_SizeY - player_pos.y;
		}
		if (pos.y < 0) {

			pos.y = m_SizeY;
		}
		else if (pos.y > m_SizeY) {

			pos.y = 0;
		}
		entity.setPosition(pos);
	}

	const auto end = m_Entities.end();
	for (auto it_i = m_Entities.begin(); it_i != end; ++it_i) {
		Entity& entity_i = **it_i;
		auto it_j = it_i;
		it_j++;
		
		for (; it_j != end; ++it_j) {
			Entity& entity_j = **it_j;

			if (entity_i.isAlive() && entity_i.isCollide(entity_j))
				entity_i.onDestroy();

			if (entity_j.isAlive() && entity_j.isCollide(entity_i))
				entity_j.onDestroy();
		}
	}

	for (auto it = m_Entities.begin(); it != m_Entities.end(); ) {
		if (!(*it)->isAlive()) {
			delete* it;
			it = m_Entities.erase(it);
		}
		else {
			++it;
		}
	}

	// IF not playing remove
	m_Sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
			return sound->getStatus() != sf::SoundSource::Status::Playing;
		});
}
