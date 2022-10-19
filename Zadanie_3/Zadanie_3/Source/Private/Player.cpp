#include "../Public/Player.h"
#include <iostream>

Player::Player(sf::Shape* Body)
	: Body(Body)
	, Speed(10.f)
	, Smooth(0.9f)
	, Velocity(0.0f, 0.0f)
	, Direction(0.0f, 0.0f)
{}

Player::Player(sf::Shape* Body, float Speed, float Smooth)
	: Body(Body)
	, Speed(Speed)
	, Smooth(Smooth)
	, Velocity(0.0f, 0.0f)
	, Direction(0.0f, 0.0f)
{}

Player::~Player()
{}

void Player::GetMovementInput(sf::Event event)
{
	float speed;
	if (event.type == sf::Event::KeyPressed)
	{
		speed = Speed;
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		speed = 0.0f;
	}
	else
	{
		return;
	}

	switch (event.key.code)
	{
		case sf::Keyboard::W:
		{
			Direction.y = -speed;
			break;
		}
		case sf::Keyboard::S:
		{
			Direction.y = speed;
			break;
		}
		case sf::Keyboard::A:
		{
			Direction.x = -speed;
			break;
		}
		case sf::Keyboard::D:
		{
			Direction.x = speed;
			break;
		}
	default:
		break;
	}
	// Display input to console
	std::cout << (char)('a' + event.key.code) << std::endl;
}

void Player::UpdatePosition(sf::Int32 DeltaTime)
{
	Velocity = Direction * (1.0f - Smooth) + Velocity * Smooth;

	Body->setPosition(Body->getPosition() + Velocity * (float)DeltaTime);
}

void Player::UpdatePositionByMouse(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		Body->setPosition(event.mouseMove.x, event.mouseMove.y);
		// Display input to console
		std::cout << "X: " << event.mouseMove.x << " Y: " << event.mouseMove.y << std::endl;
	}
}

sf::Shape* Player::getBody() const
{
	return Body;
}


