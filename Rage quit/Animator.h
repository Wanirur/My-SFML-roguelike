#pragma once
#include <SFML/Graphics.hpp>

class Animator
{
public:
	Animator(sf::Texture * texture, sf::Vector2u imageCount, float switchTime);
	~Animator();

	void update(int column, float deltaTime);

	sf::IntRect uvRect;

private:

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

	
};

