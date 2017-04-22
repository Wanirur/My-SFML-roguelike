#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform :public sf::Drawable
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void draw(sf::RenderWindow &window);
	Collider getCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

