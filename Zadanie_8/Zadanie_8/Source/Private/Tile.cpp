#include "../Public/Tile.h"

Tile::Tile()
	: Texture(sf::Texture())
	, Character(NULL)
	, HasCollider(false)
{}

Tile::Tile(sf::Texture Texture, char Character, bool HasCollider)
	: Texture(Texture)
	, Character(Character)
	, HasCollider(HasCollider)
{}
