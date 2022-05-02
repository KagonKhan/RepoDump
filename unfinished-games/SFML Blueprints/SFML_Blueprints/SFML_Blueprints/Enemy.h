#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;

	Enemy(Configuration::Textures tex_id, World& world);

	virtual int getPoints() const = 0;
	virtual void onDestroy();
};

