#include "../Public/Player.h"
#include <iostream>

Player::Player(Collision& Body)
	: m_Body(&Body)
	, Speed(10.f)
	, Smooth(0.9f)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(0.0f, 0.0f)
	, Score(0)
	, CanMove(false)
{
	Body.Owner = nullptr;
}

Player::Player(Collision& Body, float Speed, float Smooth)
	: m_Body(&Body)
	, Speed(Speed)
	, Smooth(Smooth)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(0.0f, 0.0f)
	, Score(0)
	, CanMove(false)
{
	Body.Owner = this;
}

Player::~Player() = default;

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
			m_Direction.y = -speed;
			break;
		}
		case sf::Keyboard::S:
		{
			m_Direction.y = speed;
			break;
		}
		case sf::Keyboard::A:
		{
			m_Direction.x = -speed;
			break;
		}
		case sf::Keyboard::D:
		{
			m_Direction.x = speed;
			break;
		}
	default:
		break;
	}
}

void Player::GetMouseInput(sf::Event event, sf::View CameraView, sf::RenderWindow& Window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2f Scale = sf::Vector2f(CameraView.getSize().x / Window.getSize().x,
										  CameraView.getSize().y / Window.getSize().y);

		sf::Vector2f MouseOffset = CameraView.getCenter() - (CameraView.getSize() / 2.0f);

		sf::Vector2f Dir = sf::Vector2f(sf::Mouse::getPosition(Window).x * Scale.x + MouseOffset.x - m_Body->Body->getPosition().x,
										sf::Mouse::getPosition(Window).y * Scale.y + MouseOffset.y - m_Body->Body->getPosition().y);
		// Normalize
		float Len = sqrt(Dir.x * Dir.x + Dir.y * Dir.y);
		Dir = sf::Vector2f(Dir.x / Len, Dir.y / Len);

		Dir *= Speed;

		m_Direction = Dir;
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		m_Direction = sf::Vector2f(0.0f, 0.0f);
	}
}

void Player::UpdatePosition(sf::Int32 DeltaTime)
{
	if (CanMove)
	{
		m_Velocity = m_Direction * (1.0f - Smooth) + m_Velocity * Smooth;

		m_Body->Body->setPosition(m_Body->Body->getPosition() + m_Velocity * (float)DeltaTime);
	}
}

Collision* Player::getBody() const
{
	return m_Body;
}

sf::Shape* Player::getBodyShape() const
{
	return m_Body->Body;
}


