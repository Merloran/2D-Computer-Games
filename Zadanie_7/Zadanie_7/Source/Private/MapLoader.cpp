#include "../Public/MapLoader.h"

MapLoader::MapLoader(const char* Path, float TileSize)
	: TileSize(TileSize)
	, Size(0.0f, 0.0f)
	, IsMapLoaded(false)
	, P1Start(0.0f, 0.0f)
	, P2Start(0.0f, 0.0f)
	, Exit(0.f, 0.f)
{
	std::ifstream file;
	std::string map, line;

	file.open(Path);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			map += line + "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "File not opened!" << std::endl;
	}
	Map = map;
}


void MapLoader::AddTile(const char* Path, char Character, bool HasCollider)
{
	m_Texture.loadFromFile(Path);
	if (ContainsCharacter(Character))
	{
		std::cout << "Character " << Character << " is already used for other tile" << std::endl;
		return;
	}
	Tiles.push_back(Tile(m_Texture, Character, HasCollider));
}

void MapLoader::SetDefaultTile(const char* Path)
{
	m_Texture.loadFromFile(Path);
	m_DefaultTile = Tile(m_Texture, ' ', false);
}

void MapLoader::CreateObjects()
{
	Elements.reserve(Map.length());
	Spawnable.reserve(Map.length());

	float OffsetX = 0.0f, OffsetY = 0.0f;

	bool isTilePlaced = false;
	for (int i = 0; i < Map.length(); ++i)
	{
		isTilePlaced = false;
		if (Map[i] == '\n')
		{
			OffsetX = 0.0f;
			OffsetY += TileSize;
			if (OffsetY > Size.y)
			{
				Size.y = OffsetY;
			}
			continue;
		}

		for (int j = 0; j < Tiles.size(); ++j)
		{
			if (Tiles[j].Character == Map[i])
			{
				sf::Sprite sprite(Tiles[j].Texture);
				sprite.setTextureRect(sf::IntRect(0, 0, TileSize, TileSize));
				sprite.setPosition(OffsetX, OffsetY);
				Elements.push_back(sprite);
				if (Tiles[j].HasCollider)
				{
					std::shared_ptr<Collision> C = std::make_shared<Collision>(sf::Vector2f(OffsetX + TileSize * 0.5f, OffsetY + TileSize * 0.5f),
						sf::Vector2f(TileSize, TileSize), &Tiles[j]);
					Colliders.push_back(C);
				}
				else
				{
					Spawnable.push_back(sprite.getPosition());
				}
				isTilePlaced = true;
				break;
			}
		}

		if (!isTilePlaced)
		{
			sf::Sprite sprite;
			sprite = sf::Sprite(m_DefaultTile.Texture);
			sprite.setTextureRect(sf::IntRect(0, 0, TileSize, TileSize));
			sprite.setPosition(OffsetX, OffsetY);
			Elements.push_back(sprite);
			Spawnable.push_back(sprite.getPosition());
		}

		OffsetX += TileSize;

		if (OffsetX > Size.x)
		{
			Size.x = OffsetX;
		}
	}
	SpawnExit();
}

void MapLoader::SpawnExit()
{
	int random = rand() % Spawnable.size();

	sf::Sprite sprite;
	for (int i = 0; i < Tiles.size(); ++i)
	{
		if (Tiles[i].Character == '#')
		{
			sprite = sf::Sprite(Tiles[i].Texture);
			sprite.setTextureRect(sf::IntRect(0, 0, TileSize, TileSize));
			sprite.setPosition(Spawnable[random]);
			Elements.push_back(sprite);
			Exit = Spawnable[random];
			std::shared_ptr<Collision> C = std::make_shared<Collision>(sf::Vector2f(Spawnable[random].x + TileSize * 0.5f, Spawnable[random].y + TileSize * 0.5f),
																	   sf::Vector2f(TileSize, TileSize), &Tiles[i]);
			Colliders.push_back(C);
			break;
		}
	}
	Spawnable.erase(Spawnable.begin() + random - 1);

	random = rand() % Spawnable.size();
	P1Start = Spawnable[random];

	Spawnable.erase(Spawnable.begin() + random - 1);
	random = rand() % Spawnable.size();
	P2Start = Spawnable[random];
}

bool MapLoader::CheckColliders(Player& P)
{
	for (int i = 0; i < Colliders.size(); ++i)
	{
		if ( Collision::CheckCollision(*P.getBody(), *Colliders[i]) )
		{
			Tile* t = static_cast<Tile*>(Colliders[i]->Owner);
			if (t && t->Character == '#')
			{
				P.Score++;
				return true;
			}
		}
	}
	return false;
}

void MapLoader::ClearMap()
{
	Tiles.clear();
	Elements.clear();
	Colliders.clear();
	Spawnable.clear();
	IsMapLoaded = false;
}

bool MapLoader::ContainsCharacter(char Character)
{
	for (Tile tile : Tiles)
	{
		if (tile.Character == Character)
		{
			return true;
		}
	}
	return false;
}
