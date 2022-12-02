#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Tile.h"
#include "Player.h"

class MapLoader
{
public:
	std::string Map;
	float TileSize;
	std::vector<sf::Sprite> Elements;
	std::vector<sf::Vector2f> Spawnable;
	std::vector<std::shared_ptr<Collision>> Colliders;
	std::vector<Tile> Tiles;
	sf::Vector2f Size;
	bool IsMapLoaded;
	sf::Vector2f P1Start;
	sf::Vector2f P2Start;
	sf::Vector2f Exit;

	MapLoader(const char* Path, float TileSize);

	void AddTile(const char* Path, char Character, bool HasCollider = false);

	void CreateObjects();

	void SetDefaultTile(const char* Path);

	void SpawnExit();

	bool CheckColliders(Player& P);

	void ClearMap();

private:
	Tile m_DefaultTile;
	sf::Texture m_Texture;

	bool ContainsCharacter(char Character);
};