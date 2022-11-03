#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

struct Tile
{
	sf::Texture Texture;
	char Character;

	Tile()
	: Texture(sf::Texture())
	, Character(NULL)
	{}

	Tile(sf::Texture Texture, char Character)
		: Texture(Texture)
		, Character(Character)
	{}
};

using namespace std;

class MapLoader
{
public:
	string Map;
	float TileSize;
	vector<sf::Sprite> Elements;
	vector<sf::Texture> Textures;
	vector<Tile> Tiles;
	sf::Vector2f Size;

	MapLoader(const char* Path, float TileSize);

	void AddTile(const char* Path, char Character);

	void CreateObjects();

	void SetDefaultTile(const char* Path);

private:
	Tile m_DefaultTile;
	sf::Texture m_Texture;

	bool ContainsCharacter(char Character);
};