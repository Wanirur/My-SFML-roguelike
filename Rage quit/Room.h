#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Room :public sf::Drawable, public sf::Transformable
{
public:
	Room(sf::Vector2u position,sf::Vector2u size, sf::Texture &tile_texture, sf::Vector2f tile_size);
	~Room();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector <Tile> room;

	sf::Vector2u size;

	sf::Vector2u position;

	enum TileSet
	{
		HIGHEST_POINT_OF_LEFT_UPSIDE_CORNER,
		HIGHEST_POINT_OF_UPSIDE_WALL,
		HIGHEST_POINT_OF_UPSIDE_FILAR_WALL,
		HIGHEST_POINT_OF_RIGHT_UPSIDE_CORNER,

		NOTHING = 9,
		LEFT_UPSIDE_CORNER,
		UPSIDE_WALL,
		UPSIDE_FILAR_WALL,
		RIGHT_UPSIDE_CORNER,


		LEFT_WALL = 20,
		RIGHT_WALL = 23,

		LEFT_DOWNSIDE_CORNER = 30,
		DOWNSIDE_WALL,
		RIGHT_DOWNSIDE_CORNER = 33,

		EMPTY_SPACE = 49,

		FLOOR = 59,
		DOOR = 60
	};
};

