#include "Animator.h"


Animator::Animator(sf::Texture * texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;

	currentImage.y = 0;

	uvRect.width = texture->getSize().x / imageCount.x;
	uvRect.height = texture->getSize().y / imageCount.y;

}

Animator::~Animator()
{
}

void Animator::update(int column, float deltaTime)
{
	currentImage.x = column;

	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.y++;

		if (currentImage.y >= imageCount.y)
		{
			currentImage.y = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}
