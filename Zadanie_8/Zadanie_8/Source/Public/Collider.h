#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collider
{
public:
	sf::Shape* Body;
	void* Owner;

	Collider();
	Collider(sf::Vector2f Center, float Radius, void* Owner = nullptr);
	Collider(sf::Vector2f Center, sf::Vector2f Size, void* Owner = nullptr);

	~Collider();

	// Returns vector of direction from Other to this
	sf::Vector2f CheckCollision(Collider& Other);

	static sf::Vector2f Dot(sf::Vector2f V1, sf::Vector2f V2);

	static float DotProduct(sf::Vector2f V1, sf::Vector2f V2);

	// Return Angle between vectors in degrees
	static float GetAngle(sf::Vector2f V1, sf::Vector2f V2);

	static sf::Vector2f Normalize(sf::Vector2f V);

	static float Length(sf::Vector2f V);

	static float Clamp(float x, float min, float max);

private:
	sf::CircleShape* Circle;
	sf::RectangleShape* Rectangle;

	sf::Vector2f CheckCollisionCircle(Collider& Other);

	sf::Vector2f CheckCollisionRectangle(Collider& Other);

	sf::Vector2f CheckCollisionAABB(Collider& Other);

};

