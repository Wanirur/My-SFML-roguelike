#include "Tile.h"



Tile::Tile(sf::Vector2f position, sf::Texture &texture, sf::Vector2f size)
	:FLOOR(59)
{
	this->position = position;
	this->texture = texture;
	this->size = size;

}

Tile::Tile(sf::Vector2f position, sf::Texture &texture, sf::Vector2f size, unsigned tile_number)
	:FLOOR(59), size(16.0f,16.0f)
{
	this->position = position;
	this->texture = texture;
	this->size = size;

	this->type = tile_number;

	buildTile();
}

Tile::~Tile()
{
}

void Tile::setType(unsigned int tile_number)
{
	this->type = tile_number;

	buildTile();
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &texture;

	target.draw(tile, states);
}


void Tile::buildTile()
{
	if (type == FLOOR)
		colliding = false;
	else
		colliding = true;

	tile.setPrimitiveType(sf::Quads);
	tile.resize(4);

	tile[0].position = position;
	tile[1].position = sf::Vector2f(position.x + size.x, position.y);
	tile[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	tile[3].position = sf::Vector2f(position.x, position.y + size.y);

	sf::Vector2f texCoords;
	texCoords.x = float((type % 10) * (texture.getSize().x / 10));
	texCoords.y = float((type / 10) * (texture.getSize().x / 6));

	tile[0].texCoords = texCoords;
	tile[1].texCoords = sf::Vector2f(texCoords.x + 16, texCoords.y);
	tile[2].texCoords = sf::Vector2f(texCoords.x + 16, texCoords.y + 16);
	tile[3].texCoords = sf::Vector2f(texCoords.x, texCoords.y + 16);

}
