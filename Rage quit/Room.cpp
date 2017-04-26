#include "Room.h"



Room::Room(sf::Vector2u position, sf::Vector2u size, sf::Texture &tile_texture, sf::Vector2f tile_size)
{
	this->position = position;
	this->size = size;

	for (std::size_t i = 0; i <= size.x; i++)
	{
		for (std::size_t j = 0; j <= size.y; j++)
		{
			room.push_back(Tile(sf::Vector2f(float(position.x + i), float(position.y + j)),tile_texture, tile_size));

			if (i == 0)
			{
				if (j == 0)
					room.back().setType(HIGHEST_POINT_OF_LEFT_UPSIDE_CORNER);
				else if (j == 1)
					room.back().setType(LEFT_UPSIDE_CORNER);
				else if (j == size.y)
					room.back().setType(LEFT_DOWNSIDE_CORNER);
				else
					room.back().setType(LEFT_WALL);
			}
			else if (i == size.x)
			{
				if (j == 0)
					room.back().setType(HIGHEST_POINT_OF_RIGHT_UPSIDE_CORNER);
				else if (j == 1)
					room.back().setType(RIGHT_UPSIDE_CORNER);
				else if (j == size.y)
					room.back().setType(RIGHT_DOWNSIDE_CORNER);
				else
					room.back().setType(RIGHT_WALL);
			}
			else
			{
				if (j == 0)
				{
					switch (std::rand() % 5)
					{
					case 0:
						room.back().setType(HIGHEST_POINT_OF_UPSIDE_FILAR_WALL);
						break;
					default:
						room.back().setType(HIGHEST_POINT_OF_UPSIDE_WALL);
						break;
					}
				}
				else if (j == 1)
				{
					if (room[(i + j) - 1].getType() == HIGHEST_POINT_OF_UPSIDE_FILAR_WALL)
						room.back().setType(UPSIDE_FILAR_WALL);
					else
						room.back().setType(UPSIDE_WALL);
				}
				else if (j == size.y)
					room.back().setType(DOWNSIDE_WALL);
				else
					room.back().setType(FLOOR);
			}
		}
	}


}


Room::~Room()
{
}

void Room::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < room.size(); i++)
		target.draw(room[i], states);
}
