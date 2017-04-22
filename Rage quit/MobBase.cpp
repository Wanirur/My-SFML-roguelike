#include "MobBase.h"

MobBase::MobBase(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position)
	:animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	
	body.setSize(sf::Vector2f(90.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

MobBase::~MobBase()
{
}

void MobBase::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body, states);
}
