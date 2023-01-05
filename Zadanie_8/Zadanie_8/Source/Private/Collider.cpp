#include "../Public/Collider.h"
#include "corecrt_math_defines.h"


Collider::Collider()
	: Rectangle(nullptr)
	, Circle(nullptr)
	, Body(nullptr)
	, Owner(nullptr)
{}

Collider::Collider(sf::Vector2f Center, float Radius, void* Owner)
	: Rectangle(nullptr)
	, Owner(Owner)
{
	sf::CircleShape* Temp = new sf::CircleShape(Radius);

	Body = Temp;
	Body->setFillColor(sf::Color::Red);
	Body->setOrigin(Radius, Radius);
	Body->setPosition(Center);
	Circle = Temp;
}

Collider::Collider(sf::Vector2f Center, sf::Vector2f Size, void* Owner)
	: Circle(nullptr)
	, Owner(Owner)
{
	sf::RectangleShape* Temp = new sf::RectangleShape(Size);

	Body = Temp;
	Body->setFillColor(sf::Color::Blue);
	Body->setOrigin(Size * 0.5f);
	Body->setPosition(Center);
	Rectangle = Temp;
}

Collider::~Collider()
{
	if (Body != nullptr)
	{
		delete(Body);
		Body = nullptr;
		Circle = nullptr;
		Rectangle = nullptr;
	}
}

sf::Vector2f Collider::CheckCollision(Collider& Other)
{
	if (Circle && Other.Circle)
	{
		return CheckCollisionCircle(Other);
	}
	else if (Rectangle && Other.Rectangle)
	{
		return CheckCollisionRectangle(Other);
	}
	else
	{
		if (Rectangle && Other.Circle)
		{
			return CheckCollisionAABB(Other);
		}
		else
		{
			return Other.CheckCollisionAABB(*this);
		}
	}
}

sf::Vector2f Collider::Dot(sf::Vector2f V1, sf::Vector2f V2)
{
	return sf::Vector2f(V1.x * V2.x, V1.y * V2.y);
}

float Collider::DotProduct(sf::Vector2f V1, sf::Vector2f V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

float Collider::GetAngle(sf::Vector2f V1, sf::Vector2f V2)
{
	return acos(DotProduct(V1, V2) / (Length(V1) * Length(V2))) * (180.0f / M_PI);
}

sf::Vector2f Collider::Normalize(sf::Vector2f V)
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

float Collider::Length(sf::Vector2f V)
{
	return sqrt(V.x * V.x + V.y * V.y);
}

float Collider::Clamp(float x, float min, float max)
{
	return x < min ? min : x > max ? max : x;
}

sf::Vector2f Collider::CheckCollisionCircle(Collider& Other)
{
	sf::Vector2f Direction(0.0f, 0.0f);
	if (Length(Circle->getPosition() - Other.Circle->getPosition()) < Circle->getRadius() + Other.Circle->getRadius())
	{
		sf::Vector2f V1 = Circle->getPosition(), V2 = Other.Circle->getPosition();
		float p1 = Circle->getRadius(), p2 = Other.Circle->getRadius();
		Direction = Normalize(V1 - V2);
		sf::Vector2f S = Direction * (p1 + p2 - Length(V1 - V2));

		Circle->setPosition(Circle->getPosition() + S);
	}
	return Direction;
}

sf::Vector2f Collider::CheckCollisionRectangle(Collider& Other)
{
	float r1 = Rectangle->getGlobalBounds().width + Rectangle->getGlobalBounds().left, r2 = Other.Rectangle->getGlobalBounds().width + Other.Rectangle->getGlobalBounds().left;
	float l1 = Rectangle->getGlobalBounds().left, l2 = Other.Rectangle->getGlobalBounds().left;
	float b1 = Rectangle->getGlobalBounds().height + Rectangle->getGlobalBounds().top, b2 = Other.Rectangle->getGlobalBounds().height + Other.Rectangle->getGlobalBounds().top;
	float t1 = Rectangle->getGlobalBounds().top, t2 = Other.Rectangle->getGlobalBounds().top;

	float left = r1 - l2, right = r2 - l1, top = b1 - t2, bottom = b2 - t1;
	sf::Vector2f Direction(0.0f, 0.0f);

	if (left > 0.0f && right > 0.0f && top > 0.0f && bottom > 0.0f)
	{
		left < right ? Direction.x = -left : Direction.x = right;
		top < bottom ? Direction.y = -top : Direction.y = bottom;
		Direction.x * Direction.x < Direction.y * Direction.y ? Direction.y = 0.0f : Direction.x = 0.0f;
		Rectangle->setPosition(Rectangle->getPosition() + Direction);
	}
	return Direction;
}

// Other is Circle and this is Rectangle
sf::Vector2f Collider::CheckCollisionAABB(Collider& Other)
{
	float r = Rectangle->getGlobalBounds().width + Rectangle->getGlobalBounds().left;
	float l = Rectangle->getGlobalBounds().left;
	float b = Rectangle->getGlobalBounds().height + Rectangle->getGlobalBounds().top;
	float t = Rectangle->getGlobalBounds().top;
	sf::Vector2f f, c = Other.Circle->getPosition();
	float p = Other.Circle->getRadius();
	f.x = Clamp(c.x, l, r);
	f.y = Clamp(c.y, t, b);

	float len = Length(c - f);
	float left = c.x - l + p, right = r - c.x + p, top = c.y - t + p, bottom = b - c.y + p;
	sf::Vector2f Direction(0.0f, 0.0f);
	if (len < p)
	{
		if (c == f)
		{
			left < right ? Direction.x = -left : Direction.x = right;
			top < bottom ? Direction.y = -top : Direction.y = bottom;
			Direction.x * Direction.x < Direction.y * Direction.y ? Direction.y = 0.0f : Direction.x = 0.0f;
		}
		else
		{
			Direction = (c - f) / Length(c - f) * (p - Length(c - f));
		}
		Other.Circle->setPosition(Other.Circle->getPosition() + Direction);
	}
	return Direction;
}
