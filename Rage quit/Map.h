#pragma once

#include "Configure.h"
#include <SFML/Graphics.hpp>

/*******************
* 1. Wygenerowaæ "wê¿a" - DONE!
* 2. Wygenerowaæ odnogi "wê¿a" - DONE!
* 3. Podzieliæ wê¿a na czêœci drzwiami - DONE!
* 4. Zape³niæ to pokojami
* 5. Ogarn¹æ œciany
* 6. Obiekty losowe
*/

class Map :public sf::Drawable, public sf::Transformable
{
public:
	Map(sf::Texture& texture);

	void generate();

	bool save();
	bool load();

	void buildMap();

	sf::Vector2f getEnterPosition();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum Directions
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,

		HORIZONTAL,
		VERTICAL
	};


	sf::VertexArray floor;
	sf::VertexArray walls;
	unsigned int tiles[MAP_SIZE][MAP_SIZE];
	unsigned int objects[MAP_SIZE][MAP_SIZE];
	sf::Texture texture;

	sf::Vector2f map_enter_position;

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