#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.h"
#include "Collider.h"

class MobBase :public sf::Drawable
{
public:
	MobBase(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	~MobBase();

	sf::Vector2f getPosition() { return body.getPosition(); }
	Collider getCollider() { return Collider(body); }

protected:
	sf::RectangleShape body;
	Animator animation;
	unsigned int column;
	float speed;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

