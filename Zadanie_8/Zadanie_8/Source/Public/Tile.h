#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Tile
{
public:
	sf::Texture Texture;
	char Character;
	bool HasCollider;
	
	Tile();

	Tile(sf::Texture Texture, char Character, bool HasCollider);
};

