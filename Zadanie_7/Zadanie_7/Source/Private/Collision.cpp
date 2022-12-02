#include "../Public/Collision.h"


Collision::Collision()
	: Rectangle(nullptr)
	, Circle(nullptr)
	, Body(nullptr)
	, Owner(nullptr)
{}

Collision::Collision(sf::Vector2f Center, float Radius, void* Owner)
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

Collision::Collision(sf::Vector2f Center, sf::Vector2f Size, void* Owner)
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

Collision::~Collision()
{
	if (Body != nullptr)
	{
		delete(Body);
		Body = nullptr;
		Circle = nullptr;
		Rectangle = nullptr;
	}
}

bool Collision::CheckCollision(Collision& C1, Collision& C2)
{
	if (C1.Circle && C2.Circle)
	{
		return CheckCollisionCircle(C1, C2);
	}
	else if (C1.Rectangle && C2.Rectangle)
	{
		return CheckCollisionRectangle(C1, C2);
	}
	else
	{
		if (C1.Rectangle && C2.Circle)
		{
			return CheckCollisionAABB(C1, C2);
		}
		else
		{
			return CheckCollisionAABB(C2, C1);
		}
	}
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

float Collision::Clamp(float x, float min, float max)
{
	return x < min ? min : x > max ? max : x;
}

bool Collision::CheckCollisionCircle(Collision& C1, Collision& C2)
{
	if (Length(C1.Circle->getPosition() - C2.Circle->getPosition()) < C1.Circle->getRadius() + C2.Circle->getRadius())
	{
		sf::Vector2f V1 = C1.Circle->getPosition(), V2 = C2.Circle->getPosition();
		float p1 = C1.Circle->getRadius(), p2 = C2.Circle->getRadius();

		sf::Vector2f S = Normalize(V1 - V2) * (p1 + p2 - Length(V1 - V2));

		C1.Circle->setPosition(C1.Circle->getPosition() + S);
		return true;
	}
	return false;
}

bool Collision::CheckCollisionRectangle(Collision& C1, Collision& C2)
{
	float r1 = C1.Rectangle->getGlobalBounds().width + C1.Rectangle->getGlobalBounds().left, r2 = C2.Rectangle->getGlobalBounds().width + C2.Rectangle->getGlobalBounds().left;
	float l1 = C1.Rectangle->getGlobalBounds().left, l2 = C2.Rectangle->getGlobalBounds().left;
	float b1 = C1.Rectangle->getGlobalBounds().height + C1.Rectangle->getGlobalBounds().top, b2 = C2.Rectangle->getGlobalBounds().height + C2.Rectangle->getGlobalBounds().top;
	float t1 = C1.Rectangle->getGlobalBounds().top, t2 = C2.Rectangle->getGlobalBounds().top;

	float left = r1 - l2, right = r2 - l1, top = b1 - t2, bottom = b2 - t1;
	sf::Vector2f V;

	if (left > 0.0f && right > 0.0f && top > 0.0f && bottom > 0.0f)
	{
		left < right ? V.x = -left : V.x = right;
		top < bottom ? V.y = -top : V.y = bottom;
		V.x * V.x < V.y * V.y ? V.y = 0.0f : V.x = 0.0f;
		C1.Rectangle->setPosition(C1.Rectangle->getPosition() + V);
		return true;
	}
	return false;
}

// C1 is Rectangle C2 is Circle
bool Collision::CheckCollisionAABB(Collision& C1, Collision& C2)
{
	float r = C1.Rectangle->getGlobalBounds().width + C1.Rectangle->getGlobalBounds().left;
	float l = C1.Rectangle->getGlobalBounds().left;
	float b = C1.Rectangle->getGlobalBounds().height + C1.Rectangle->getGlobalBounds().top;
	float t = C1.Rectangle->getGlobalBounds().top;
	sf::Vector2f f, c = C2.Circle->getPosition();
	float p = C2.Circle->getRadius();
	f.x = Clamp(c.x, l, r);
	f.y = Clamp(c.y, t, b);

	float len = Length(c - f);
	float left = c.x - l + p, right = r - c.x + p, top = c.y - t + p, bottom = b - c.y + p;
	if (len < p)
	{
		sf::Vector2f V;
		if (c == f)
		{
			left < right ? V.x = -left : V.x = right;
			top < bottom ? V.y = -top : V.y = bottom;
			V.x * V.x < V.y * V.y ? V.y = 0.0f : V.x = 0.0f;
		}
		else
		{
			V = (c - f) / Length(c - f) * (p - Length(c - f));
		}
		C2.Circle->setPosition(C2.Circle->getPosition() + V);
		return true;
	}
	return false;
}
