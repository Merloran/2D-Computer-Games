#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collision
{
public:
	sf::CircleShape Body;
	sf::FloatRect Border;
	sf::Vector2f Velocity;
	float Speed;

	Collision(sf::Vector2f Center, float Radius, float Speed, sf::Vector2f Velocity = sf::Vector2f(1.f, 1.f), sf::FloatRect Border = sf::FloatRect(0.f, 0.f, 1024.f, 768.f));

	static void CheckCollision(Collision& C1, Collision& C2, bool IsSeparating, bool IsReflecting);

	void Move(int DeltaTime);

	static void Reflect(Collision& C1, Collision& C2);

	static sf::Vector2f Separation(Collision& C1, Collision& C2);

	static sf::Vector2f Dot(sf::Vector2f V1, sf::Vector2f V2);

	static float DotProduct(sf::Vector2f V1, sf::Vector2f V2);

	static sf::Vector2f Normalize(sf::Vector2f V);

	static float Length(sf::Vector2f V);
};

