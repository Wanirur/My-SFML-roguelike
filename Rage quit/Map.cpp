#include "Map.h"

Map::Map(sf::Texture& texture, sf::Vector2u size, unsigned branches_quantity, sf::Vector2f tile_size)
	:enter_position(std::rand() % size.x, std::rand() % 5 + (size.y - 5)), exit_position(std::rand() % size.x, std::rand() % 5 + 1), path(enter_position, exit_position, branches_quantity, texture, tile_size)
{
	this->texture = texture;
	this->size = size;
}

void Map::generate()
{

	//generating doors

}


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(path, states);

	for (std::size_t i = 0; i < rooms.size(); i++)
		target.draw(rooms[i], states);
}

bool Map::save()
{
	return false;
}

bool Map::load()
{
	return false;
}

sf::Vector2f Map::getEnterPosition()
{
	return sf::Vector2f(enter_position);
}
