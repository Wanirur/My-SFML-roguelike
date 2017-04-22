#pragma once
#include "MobBase.h"

class Player :public MobBase
{
public:
	Player(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	~Player();

	void update(float deltaTime);
};

