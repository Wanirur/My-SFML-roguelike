#include "Map.h"

Map::Map(sf::Texture& texture)
{
	this->texture = texture;
	
}

void Map::generate()
{
	//filling the map with empty space
	for (std::size_t i = 0; i < MAP_SIZE; i++)
	{
		for (std::size_t j = 0; j < MAP_SIZE; j++)
			tiles[i][j] = EMPTY_SPACE;
	}

	//generating of enter and exit
	sf::Vector2u enter_position;
	sf::Vector2u exit_position;

	int enter_area = std::rand() % 4;

	switch (enter_area) 
	{
	case UP:
		enter_position.x = std::rand() % (MAP_SIZE - 2) + 1;  
		enter_position.y = std::rand() % 5 + 1;

		exit_position.x = std::rand() % (MAP_SIZE - 2) + 1;
		exit_position.y = std::rand() % (5 + (MAP_SIZE - 5)) - 1;
		break;
	case RIGHT:
		enter_position.x = std::rand() % (5 + (MAP_SIZE - 5)) - 1;
		enter_position.y = std::rand() % (MAP_SIZE - 2) + 1;

		exit_position.x = std::rand() % 5 + 1;
		exit_position.y = std::rand() % (MAP_SIZE - 2) + 1;
		break;
	case DOWN:
		enter_position.x = std::rand() % MAP_SIZE;
		enter_position.y = std::rand() % 5 + (MAP_SIZE - 5);

		exit_position.x = std::rand() % MAP_SIZE;
		exit_position.y = std::rand() % 5 + 1;
		break;
	case LEFT:
		enter_position.x = std::rand() % 5 + 1;
		enter_position.y = std::rand() % (MAP_SIZE - 2) + 1;

		exit_position.x = (std::rand() % 5 + (MAP_SIZE - 5)) - 1;
		exit_position.y = std::rand() % (MAP_SIZE - 2) + 1;
		break;
	}
	
	tiles[enter_position.x][enter_position.y] = DOOR;
	map_enter_position.x = enter_position.x*TILE_SIZE;
	map_enter_position.y = enter_position.y*TILE_SIZE;
	tiles[exit_position.x][exit_position.y] = DOOR;

	//generating the path between enter and exit

	std::vector <sf::Vector2u> path; //<- this vector stores coordinates of all tiles of path. First and last tile is enter and exit. Its only two lines and makes next steps of generating map much easier and faster
	{
		unsigned int x = enter_position.x;
		unsigned int y = enter_position.y;

		unsigned int x_before_changes = enter_position.x;
		unsigned int y_before_changes = enter_position.y;

		while (!(x == exit_position.x && y == exit_position.y))
		{
			int orientation = std::rand() % 2 + 4;

			switch (orientation)
			{
			case HORIZONTAL:
				if (x < exit_position.x)
					++x;
				else if (x > exit_position.x)
					--x;
				else
				{
					if (std::max(y, exit_position.y) - std::min(y, exit_position.y) >= 5)
					{
						int direction = std::rand() % 2 + 2;

						switch (direction)
						{
						case LEFT: 
							--x;
							break;
						case RIGHT: 
							++x;
							break;
						}
					}
					else
					{
						if (y < exit_position.y)
							++y;
						else
							--y;
					}
				}
				break;
			case VERTICAL:
				if (y < exit_position.y)
					++y;
				else if (y > exit_position.y)
					--y;
				else
				{
					if (std::max(x, exit_position.x) - std::min(x, exit_position.x) >= 5)
					{
						int direction = std::rand() % 2;

						switch (direction)
						{
						case UP:
							--y;
							break;
						case DOWN:
							++y;
							break;
						}
					}
					else
					{
						if (x < exit_position.x)
							++x;
						else
							--x;
					}
				}
				break;
			}
			if (tiles[x][y] != FLOOR && tiles[x][y] != DOOR)
			{
				tiles[x][y] = FLOOR;
				path.push_back(sf::Vector2u(x, y));

				x_before_changes = x;
				y_before_changes = y;
			}
			else if (tiles[x][y] == FLOOR)
			{
				x = x_before_changes;
				y = y_before_changes;
			}
		}
	}
	//generating branches of path

	std::vector <sf::Vector2u> branches_begins;//<- this vector stores coordinates of tiles which are begins of each branche. They are in path vector too
	
	for (int i = 0; i < BRANCHES_QUANTITY; i++)
		branches_begins.push_back(path[(i + 1)*path.size() / (BRANCHES_QUANTITY + 1)]);

	Directions MAP_ORIENTATION;

	if (enter_area == UP || enter_area == DOWN)
		MAP_ORIENTATION = VERTICAL;
	else
		MAP_ORIENTATION = HORIZONTAL;

	std::vector <sf::Vector2u> branches_tiles;//<- this vector stores coordinates of all tiles of all branches
	{
		int failed_tries = 0;
		bool done = false;
		for (std::vector<sf::Vector2u>::iterator i = branches_begins.begin(); i != branches_begins.end(); i++)
		{
			while(!done)
			{
				sf::Vector2u branche_end;
				if (MAP_ORIENTATION == VERTICAL)
				{
					branche_end.x = std::rand() % std::max(MAP_SIZE - i->x, unsigned(std::abs(0 - signed(i->x))));
					branche_end.y = std::rand() % 5 + (i->y - 2);
				}
				else
				{
					branche_end.x = std::rand() % 5 + (i->x - 2);
					branche_end.y = std::rand() % std::max(MAP_SIZE - i->y, unsigned(std::abs(0 - signed(i->y))));
				}

				unsigned int x = i->x;
				unsigned int y = i->y;

				unsigned int x_before_changes = i->x;
				unsigned int y_before_changes = i->y;

				while (!(x == branche_end.x && y == branche_end.y))
				{
					int orientation = std::rand() % 2 + 4;

					switch (orientation)
					{
					case VERTICAL:
						if (x < branche_end.x)
							++x;
						else if (x > branche_end.x)
							--x;
						
						else
						{
							if (std::max(y, branche_end.y) - std::min(y, branche_end.y) >= 5)
							{
								int direction = std::rand() % 2 + 2;

								switch (direction)
								{
								case LEFT:
									--x;
									break;
								case RIGHT:
									++x;
									break;
								}
							}
							else
							{
								if (y < branche_end.y)
									++y;
								else
									--y;
							}
						}
						break;
					case HORIZONTAL:
						if (y < branche_end.y)
							++y;
						else if (y > branche_end.y)
							--y;
						else
						{
							if (std::max(x, branche_end.x) - std::min(x, branche_end.x) >= 5)
							{
								int direction = std::rand() % 2;

								switch (direction)
								{
								case UP:
									--y;
									break;
								case DOWN:
									++y;
									break;
								}
							}
							else
							{
								if (x < branche_end.x)
									++x;
								else
									--x;
							}
						}
						break;
					}
					if (tiles[x][y] != FLOOR && tiles[x][y] != DOOR)
					{
						tiles[x][y] = FLOOR;

						branches_tiles.push_back(sf::Vector2u(x, y));
						x_before_changes = x;
						y_before_changes = y;

						failed_tries = 0;
					}
					else if (tiles[x][y] == FLOOR)
					{
						x = x_before_changes;
						y = y_before_changes;

						++failed_tries;
					}

					if (failed_tries >= 10)
					{
						for (std::vector<sf::Vector2u>::iterator j = branches_tiles.begin(); j != branches_tiles.end(); j++)
							tiles[j->x][j->y] = EMPTY_SPACE;
						branches_tiles.clear();
						break;
					}
					else
						done = true;
				}

			}
		}
	}

	for (std::vector<sf::Vector2u>::iterator i = branches_tiles.begin(); i != branches_tiles.end(); i++) // loading branches tiles to the path tiles
		path.push_back(*i);

	//generating doors

	std::vector <sf::Vector2u> door_tiles;
	{
		int rooms_quantity = std::rand() % 8 + 10;
		int tiles_quantity = path.size();

		for (std::size_t i = 0; i < rooms_quantity; i++)
		{
			int tile_number = i*(tiles_quantity / rooms_quantity);

			tiles[path[tile_number].x][path[tile_number].y] = DOOR;
			door_tiles.push_back(path[tile_number]);
		}
	}

	//rooms generating

	for (std::size_t i = door_tiles.size() - 1; i > 0; i--)
	{
		sf::IntRect room;
		
		if (std::max(door_tiles[i - 1].y, door_tiles[i].y) - std::min(door_tiles[i - 1].y, door_tiles[i].y) > std::max(door_tiles[i - 1].x, door_tiles[i].x) - std::min(door_tiles[i - 1].x, door_tiles[i].x))
		{
			room.top = door_tiles[i].y - 1;
			room.height = std::max(door_tiles[i - 1].y, door_tiles[i].y) - std::min(door_tiles[i - 1].y, door_tiles[i].y);

			room.width = std::rand() % 5 + 5;
			room.left = door_tiles[i].x - room.width / 2;
		}
		else
		{
			room.left = door_tiles[i].x;
			room.width = std::max(door_tiles[i - 1].x, door_tiles[i].x) - std::min(door_tiles[i - 1].x, door_tiles[i].x);
			
			room.height = std::rand() % 5 + 5;
			room.top = door_tiles[i].y - room.height / 2;
		}

		for (std::size_t x = 0; x <= room.width; x++)
		{
			for (std::size_t y = 0; y <= room.height; y++)
			{
				if (tiles[room.left + x][room.top + y] != DOOR)
				{
					if (x == 0)
					{
						if (y == 0)
							tiles[room.left + x][room.top + y] = HIGHEST_POINT_OF_LEFT_UPSIDE_CORNER;
						else if (y == 1)
							tiles[room.left + x][room.top + y] = LEFT_UPSIDE_CORNER;
						else if (y == room.height)
							tiles[room.left + x][room.top + y] = LEFT_DOWNSIDE_CORNER;
						else
							tiles[room.left + x][room.top + y] = LEFT_WALL;
					}
					else if (x == room.width)
					{
						if (y == 0)
							tiles[room.left + x][room.top + y] = HIGHEST_POINT_OF_RIGHT_UPSIDE_CORNER;
						else if (y == 1)
							tiles[room.left + x][room.top + y] = RIGHT_UPSIDE_CORNER;
						else if (y == room.height)
							tiles[room.left + x][room.top + y] = RIGHT_DOWNSIDE_CORNER;
						else
							tiles[room.left + x][room.top + y] = RIGHT_WALL;
					}
					else
					{
						if (y == 0)
							tiles[room.left + x][room.top + y] = HIGHEST_POINT_OF_UPSIDE_WALL;
						else if (y == 1)
							tiles[room.left + x][room.top + y] = UPSIDE_WALL;
						else if (y == room.height)
							tiles[room.left + x][room.top + y] = DOWNSIDE_WALL;
						else
							tiles[room.left + x][room.top + y] = FLOOR;

					}
				}
			}
		}
	}
}


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &texture;

	target.draw(floor, states);
	target.draw(walls, states);
}

bool Map::save()
{
	return false;
}

bool Map::load()
{
	return false;
}

void Map::buildMap()
{
	floor.setPrimitiveType(sf::Quads);
	floor.resize(MAP_SIZE*MAP_SIZE * 4);

	walls.setPrimitiveType(sf::Quads);
	walls.resize(MAP_SIZE*MAP_SIZE * 4);

	for (std::size_t i = 0; i < MAP_SIZE; i++)
	{
		for (std::size_t j = 0; j < MAP_SIZE; j++)
		{
			int tile_number = tiles[i][j];
			sf::Vector2u current_image(9, 5);
			sf::Vector2u current_image_walls(9,0);

			switch (tile_number)
			{
			case EMPTY_SPACE:
				current_image.x = 9;
				current_image.y = 4;
				break;
			case DOOR:
				current_image_walls.x = 1;
				current_image_walls.y = 4;
				break;
			default:
				current_image_walls.x = tile_number % 10;
				current_image_walls.y = tile_number / 10;
				break;
			}

			int x = current_image.x * TEX_TILE_SIZE;
			int y = current_image.y * TEX_TILE_SIZE;

			sf::Vertex * current_tile = &floor[(i + j * MAP_SIZE) * 4];

			current_tile[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
			current_tile[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
			current_tile[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
			current_tile[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

			current_tile[0].texCoords = sf::Vector2f(float(x),float(y));
			current_tile[1].texCoords = sf::Vector2f(float(x + TEX_TILE_SIZE), float(y));
			current_tile[2].texCoords = sf::Vector2f(float(x + TEX_TILE_SIZE), float(y + TEX_TILE_SIZE));
			current_tile[3].texCoords = sf::Vector2f(float(x), float(y + TEX_TILE_SIZE));

			int x_walls = current_image_walls.x * TEX_TILE_SIZE;
			int y_walls = current_image_walls.y * TEX_TILE_SIZE;

			sf::Vertex * current_wall_tile = &walls[(i + j*MAP_SIZE) * 4];

			current_wall_tile[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
			current_wall_tile[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
			current_wall_tile[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
			current_wall_tile[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);
			
			current_wall_tile[0].texCoords = sf::Vector2f(float(x_walls), float(y_walls));
			current_wall_tile[1].texCoords = sf::Vector2f(float(x_walls + TEX_TILE_SIZE), float(y_walls));
			current_wall_tile[2].texCoords = sf::Vector2f(float(x_walls + TEX_TILE_SIZE), float(y_walls + TEX_TILE_SIZE));
			current_wall_tile[3].texCoords = sf::Vector2f(float(x_walls), float(y_walls + TEX_TILE_SIZE));
		}
	}
}

sf::Vector2f Map::getEnterPosition()
{
	return map_enter_position;
}
