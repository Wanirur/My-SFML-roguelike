#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Map.h"
#include "Configure.h"

void resize(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_SIZE * aspectRatio, VIEW_SIZE);
}

int main()
{
	std::srand(std::clock());

	sf::RenderWindow window(sf::VideoMode(512,512),"Rage quit - worst game you have ever seen");

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_SIZE, VIEW_SIZE));

	sf::Texture player_texture;
	if (!player_texture.loadFromFile("RedAvatar.png"))
		return -1;

	sf::Texture map_texture;
	if (!map_texture.loadFromFile("Walls.png"))
		return -1;

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(100.0f, 0.0f));

	Map map(map_texture);
	map.generate();
	map.buildMap();

	Player player(&player_texture, sf::Vector2u(4, 5), 0.1f, 1390.0f, map.getEnterPosition());

	float delta_time;
	sf::Clock clock;

	while (window.isOpen())
	{
		delta_time = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resize(window,view);
				break;
			}
		}

		player.update(delta_time);

		platform1.getCollider().checkCollision(player.getCollider(), 0.0f);
		platform2.getCollider().checkCollision(player.getCollider(), 1.0f);

		view.setCenter(player.getPosition());
		

		window.clear();

		window.setView(view);

		window.draw(map);

		window.draw(player);
		window.draw(platform1);
		window.draw(platform2);

		window.display();
	}

	return 0;
}