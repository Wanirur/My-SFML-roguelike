#pragma once

#include <SFML/Graphics.hpp>

class Tile :public sf::Drawable, public sf::Transformable
{
public:
	Tile(sf::Vector2f position, sf::Texture &texture, sf::Vector2f size);
	Tile(sf::Vector2f position, sf::Texture &texture, sf::Vector2f size, unsigned tile_number);
	~Tile();

	void setType(unsigned int tile_number);

	unsigned int getType() const
	{
		return type;
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void buildTile();

	const int FLOOR;

	unsigned int type;
	bool colliding;

	sf::Vector2f size;
	sf::Vector2f position;
	
	sf::VertexArray tile;
	sf::Texture texture;
};

