#include "../Public/Collision.h"


Collision::Collision(sf::Vector2f Center, float Radius, float Speed, sf::Vector2f Velocity, sf::FloatRect Border)
	: Velocity(Normalize(Velocity))
	, Speed(Speed)
	, Border(Border)
{
	Body = sf::CircleShape(Radius);
	Body.setFillColor(sf::Color::Red);
	Body.setOrigin(Radius, Radius);
	Body.setPosition(Center);
}

void Collision::CheckCollision(Collision& C1, Collision& C2, bool IsSeparating, bool IsReflecting)
{
	if (Length(C1.Body.getPosition() - C2.Body.getPosition()) < C1.Body.getRadius() + C2.Body.getRadius())
	{
		sf::Vector2f S = Separation(C1, C2);

		if (IsSeparating)
		{
			C1.Body.setPosition(C1.Body.getPosition() + S);
		}

		if (IsReflecting)
		{
			Reflect(C1, C2);
		}
	}
}

void Collision::Move(int DeltaTime)
{
	float X = Body.getPosition().x;
	float Y = Body.getPosition().y;
	float R = Body.getRadius();

	if (X - R <= Border.left && Velocity.x <= 0.f)
	{
		Body.setPosition(Border.left + R, Body.getPosition().y);
		Velocity.x *= -1.f;
	}
	else if (X + R >= Border.width && Velocity.x >= 0.f)
	{
		Body.setPosition(Border.width - R, Body.getPosition().y);
		Velocity.x *= -1.f;
	}

	if (Y - R <= Border.top && Velocity.y <= 0.f)
	{
		Body.setPosition(Body.getPosition().x, Border.top + R);
		Velocity.y *= -1.f;
	}
	else if (Y + R >= Border.height && Velocity.y >= 0.f)
	{
		Body.setPosition(Body.getPosition().x, Border.height - R);
		Velocity.y *= -1.f;
	}

	Body.setPosition(Body.getPosition() + Velocity * Speed * (float)DeltaTime);
}

void Collision::Reflect(Collision& C1, Collision& C2)
{
	sf::Vector2f V1 = C1.Velocity;
	sf::Vector2f V2 = C2.Velocity;

	sf::Vector2f X1 = C1.Body.getPosition();
	sf::Vector2f X2 = C2.Body.getPosition();
	C1.Velocity = V1 - 2 * C2.Body.getRadius() / (C1.Body.getRadius() + C2.Body.getRadius())
		* DotProduct(V1 - V2, X1 - X2) / powf(Length(X1 - X2), 2.0f) * (X1 - X2);

	C2.Velocity = V2 - 2 * C1.Body.getRadius() / (C1.Body.getRadius() + C2.Body.getRadius())
		* DotProduct(V2 - V1, X2 - X1) / powf(Length(X2 - X1), 2.0f) * (X2 - X1);
}

sf::Vector2f Collision::Separation(Collision& C1, Collision& C2)
{
	return Normalize(C1.Body.getPosition() - C2.Body.getPosition()) * 
		  (C1.Body.getRadius() + C2.Body.getRadius() - Length(C1.Body.getPosition() - C2.Body.getPosition()));
}

sf::Vector2f Collision::Dot(sf::Vector2f V1, sf::Vector2f V2)
{
	return sf::Vector2f(V1.x * V2.x, V1.y * V2.y);
}

float Collision::DotProduct(sf::Vector2f V1, sf::Vector2f V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

sf::Vector2f Collision::Normalize(sf::Vector2f V)
{
	float len = Length(V);
	if (len == 0)
	{
		return sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		return V / len;
	}
}

float Collision::Length(sf::Vector2f V)
{
	return sqrt(V.x * V.x
			  + V.y * V.y);
}
