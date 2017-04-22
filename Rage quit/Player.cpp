#include "Player.h"


Player::Player(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position)
	:MobBase(texture,imageCount,switchTime,speed, position)
{
}

Player::~Player()
{
}

void Player::update(float deltaTime) 
{
	sf::Vector2f movement(0.0f, 0.0f);
	enum Direction
	{
		DOWN,
		RIGHT,
		LEFT,
		UP
	};
	Direction direction = DOWN;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= speed*deltaTime;
		direction = LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += speed*deltaTime;
		direction = RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y -= speed*deltaTime;
		direction = UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += speed*deltaTime;
		direction = DOWN;
	}

	body.setTextureRect(animation.uvRect);

	if (movement != sf::Vector2f(0.0f,0.0f))
	{
		animation.update(direction, deltaTime);
		body.setTextureRect(animation.uvRect);
		body.move(movement);
	}
	else
	{
		animation.uvRect.top = 0;
	}
}

