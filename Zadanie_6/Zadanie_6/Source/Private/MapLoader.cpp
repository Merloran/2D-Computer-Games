#include "../Public/MapLoader.h"

MapLoader::MapLoader(const char* Path, float TileSize)
	: TileSize(TileSize)
	, Size(sf::Vector2f(0.0f, 0.0f))
{
	ifstream file;
	string map, line;

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
		cout << "File not opened!" << endl;
	}
	Map = map;

	Elements.reserve(Map.length());
}

void MapLoader::AddTile(const char* Path, char Character)
{
	m_Texture.loadFromFile(Path);
	if (ContainsCharacter(Character))
	{
		cout << "Character " << Character << " is already used for other tile" << endl;
		return;
	}
	Tiles.push_back(Tile(m_Texture, Character));
}

void MapLoader::SetDefaultTile(const char* Path)
{
	m_Texture.loadFromFile(Path);
	m_DefaultTile = Tile(m_Texture, ' ');
}

void MapLoader::CreateObjects()
{
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
		}
		OffsetX += TileSize;
		if (OffsetX > Size.x)
		{
			Size.x = OffsetX;
		}
	}
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
