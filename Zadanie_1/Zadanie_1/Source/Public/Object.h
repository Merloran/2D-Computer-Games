#pragma once

#include <SFML/Graphics.hpp>

class Object
{
public:
	Object();

	Object(const char* Path, sf::IntRect Area = sf::IntRect(0, 0, 100, 100), sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f));

	/** Update position by velocity */
	void UpdatePostion();

	sf::Sprite GetSprite();

	sf::Vector2f Velocity;

	__forceinline void SetPosition(float X, float Y)
	{
		Sprite.setPosition(X, Y);
	}

	__forceinline float GetX()
	{
		return Sprite.getPosition().x;
	}

	__forceinline float GetY()
	{
		return Sprite.getPosition().y;
	}

	__forceinline float GetWidth()
	{
		return Sprite.getGlobalBounds().width;
	}

	__forceinline float GetHeight()
	{
		return Sprite.getGlobalBounds().height;
	}
protected:
	sf::Texture Texture;

	sf::Sprite Sprite;
};

