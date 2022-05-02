#include "Saucer.h"

#include "Collision.h" //Collision
#include "Enemy.h" //Enemy
#include "Player.h" //Player
#include "Saucer.h" //Saucer
#include "Meteor.h" //Meteor
#include "World.h" //World
#include "Shoot.h"

bool Saucer::isCollide(const Entity& other) const
{
    if (dynamic_cast<const ShootSaucer*>(&other) == nullptr) {
        return Collision::circleTest(m_Sprite, other.m_Sprite);
    }
    return false;
}

void Saucer::update(sf::Time deltaTime)
{
    float seconds = deltaTime.asSeconds();
    Entity* near = nullptr;
    float near_distance = 300;
    
    for (Entity* entity_ptr : m_World.getEntities()) {
        if (entity_ptr != this && (dynamic_cast<const Meteor*>(entity_ptr) || dynamic_cast<const ShootPlayer*>(entity_ptr))) {
            float x = getPosition().x - entity_ptr->getPosition().x;
            float y = getPosition().y - entity_ptr->getPosition().y;
            float distance = std::sqrt(x*x + y*y);

            if (distance < near_distance) {
                near_distance = distance;
                near = entity_ptr;
            }
        }
    }

    if (near != nullptr) {
        sf::Vector2f pos = near->getPosition() - getPosition();
        
        float angle_rad = std::atan2(pos.y, pos.x);

        m_Impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
    }

    m_Sprite.move(seconds * m_Impulse);
}

void Saucer::onDestroy()
{
    Enemy::onDestroy();
    m_World.Add(Configuration::Sounds::Boom2);
}

void Saucer::newSaucer(World& world)
{
    Saucer* res = nullptr;
    
    if (random(0.f, 1.f) > Configuration::getScore() / 40000.f)
        res = new BigSaucer(world);
    else
        res = new SmallSaucer(world);

    res->setPosition(random(0, 1) * world.getX(), random(0.f, (float)world.getY()));

    world.Add(res);
}



BigSaucer::BigSaucer(World& world)
    : Saucer(Configuration::Textures::BigSaucer, world)
{
    m_World.Add(Configuration::Sounds::SaucerSpawn1);
    m_Impulse *= 300.f;
}

int BigSaucer::getPoints() const
{
    return 50;
}



SmallSaucer::SmallSaucer(World& world)
    : Saucer(Configuration::Textures::SmallSaucer, world)
{
    m_TimeSinceLastShoot = sf::Time::Zero;
    m_World.Add(Configuration::Sounds::SaucerSpawn2);
    m_Impulse *= 400.f;
}

int SmallSaucer::getPoints() const
{
    return 200;
}

void SmallSaucer::update(sf::Time deltaTime)
{
    Saucer::update(deltaTime);
    m_TimeSinceLastShoot += deltaTime;

    if (m_TimeSinceLastShoot > sf::seconds(1.5)) {
        if (Configuration::player != nullptr)
            m_World.Add(new ShootSaucer(*this));
        m_TimeSinceLastShoot = sf::Time::Zero;
    }
}