#include "Meteor.h"

bool Meteor::isCollide(const Entity& other) const
{
    if (dynamic_cast<const Meteor*>(&other) == nullptr)
        return Collision::circleTest(m_Sprite, other.m_Sprite);

    return false;
}

void Meteor::update(sf::Time deltaTime)
{
    float seconds = deltaTime.asSeconds();
    m_Sprite.move(seconds * m_Impulse);
}



BigMeteor::BigMeteor(World& world)
    : Meteor((Configuration::Textures)random(Configuration::Textures::BigMeteor1, Configuration::Textures::BigMeteor4), world)
{
    m_Impulse *= 100.f;
}

int BigMeteor::getPoints() const
{
    return 20;
}

void BigMeteor::onDestroy()
{
    Meteor::onDestroy();

    int nb = random(2, 3);
    for (int i = 0; i < nb; ++i) {
        MediumMeteor* meteor = new MediumMeteor(m_World);
        meteor->setPosition(this->getPosition());
        m_World.Add(meteor);
    }
    m_World.Add(Configuration::Sounds::Explosion1);
}



MediumMeteor::MediumMeteor(World& world)
    : Meteor((Configuration::Textures)random(Configuration::Textures::MediumMeteor1, Configuration::Textures::MediumMeteor2), world)
{
    m_Impulse *= 200.f;
}

int MediumMeteor::getPoints() const
{
    return 60;
}

void MediumMeteor::onDestroy()
{
    Meteor::onDestroy();

    int nb = random(2, 3);
    for (int i = 0; i < nb; ++i) {
        SmallMeteor* meteor = new SmallMeteor(m_World);
        meteor->setPosition(this->getPosition());
        m_World.Add(meteor);
    }
    m_World.Add(Configuration::Sounds::Explosion2);
}



SmallMeteor::SmallMeteor(World& world)
    : Meteor((Configuration::Textures)random(Configuration::Textures::SmallMeteor1, Configuration::Textures::SmallMeteor4), world)
{
    m_Impulse *= 300.f;
}

int SmallMeteor::getPoints() const
{
    return 100;
}

void SmallMeteor::onDestroy()
{
    Meteor::onDestroy();

    m_World.Add(Configuration::Sounds::Explosion3);
}