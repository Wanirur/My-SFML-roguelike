#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Path :public sf::Drawable, public sf::Transformable
{
public:
	Path(sf::Vector2u begin_position,sf::Vector2u end_position, unsigned int branches_quantity, sf::Texture &tileset, sf::Vector2f tile_size);
	~Path();

	std::size_t getSize() const;
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void buildPath(sf::Vector2f tile_size);

	enum Directions
	{
		HORIZONTAL,
		VERTICAL
	};

	std::vector <Tile> path;

	sf::Vector2u begin_position;
	sf::Vector2u end_position;

	unsigned int branches_quantity;

	sf::Texture tileset;

	const int FLOOR;
};

