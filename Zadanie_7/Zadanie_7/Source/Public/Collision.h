#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collision
{
public:
	sf::Shape* Body;
	void* Owner;

	Collision();
	Collision(sf::Vector2f Center, float Radius, void* Owner = nullptr);
	Collision(sf::Vector2f Center, sf::Vector2f Size, void* Owner = nullptr);

	~Collision();

	static bool CheckCollision(Collision& C1, Collision& C2);

	static sf::Vector2f Dot(sf::Vector2f V1, sf::Vector2f V2);

	static float DotProduct(sf::Vector2f V1, sf::Vector2f V2);

	static sf::Vector2f Normalize(sf::Vector2f V);

	static float Length(sf::Vector2f V);

	static float Clamp(float x, float min, float max);

private:
	sf::CircleShape* Circle;
	sf::RectangleShape* Rectangle;

	static bool CheckCollisionCircle(Collision& C1, Collision& C2);

	static bool CheckCollisionRectangle(Collision& C1, Collision& C2);

	static bool CheckCollisionAABB(Collision& C1, Collision& C2);

};

