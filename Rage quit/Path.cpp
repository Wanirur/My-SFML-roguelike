#include "Path.h"



Path::Path(sf::Vector2u begin_position, sf::Vector2u end_position, unsigned int branches_quantity, sf::Texture &tileset)
	:FLOOR(59)
{
	this->begin_position = begin_position;
	this->end_position = end_position;
	this->branches_quantity = branches_quantity;
	this->tileset = tileset;

	buildPath();
}

Path::~Path()
{
}

void Path::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < path.size(); i++)
		target.draw(path[i], states);
}

void Path::buildPath()
{
	sf::Vector2u tile_generating(begin_position);

	while (tile_generating != end_position)
	{
		switch (std::rand() % 2)
		{
		case HORIZONTAL:
			if (tile_generating.x < end_position.x)
				++tile_generating.x;
			else if (tile_generating.x > end_position.x)
				--tile_generating.x;
			else
			{
				if (std::max(tile_generating.y, end_position.y) - std::min(tile_generating.y, end_position.y) < 5)
				{
					if (tile_generating.y < end_position.y)
						++tile_generating.y;
					else 
						--tile_generating.y;
				}
				else
				{
					switch (std::rand() % 2)
					{
					case 0:
						++tile_generating.x;
						break;
					case 1:
						--tile_generating.x;
						break;
					}
				}
			}
			break;
		case VERTICAL:
			if (tile_generating.y < end_position.y)
				++tile_generating.y;
			else if (tile_generating.x > end_position.y)
				--tile_generating.y;
			else
			{
				if (std::max(tile_generating.x, end_position.x) - std::min(tile_generating.x, end_position.x) < 5)
				{
					if (tile_generating.x < end_position.x)
						++tile_generating.x;
					else
						--tile_generating.x;
				}
				else
				{
					switch (std::rand() % 2)
					{
					case 0:
						++tile_generating.y;
						break;
					case 1:
						--tile_generating.y;
						break;
					}
				}
			}
			break;
		}
		path.push_back(Tile(sf::Vector2f(tile_generating), tileset, FLOOR));

		for (std::size_t i = 0; i < path.size() - 1; i++)
		{
			if (path[i].getPosition() == path.back().getPosition())
				path.pop_back();
		}
	}
}
