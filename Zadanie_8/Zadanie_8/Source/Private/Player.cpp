#include "../Public/Player.h"
#include <iostream>

Player::Player(Collider& Body)
	: m_Body(&Body)
	, Speed(10.f)
	, Smooth(0.9f)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(0.0f, 0.0f)
	, Score(0)
	, CanMove(false)
	, m_JumpCounter(0)
{
	Body.Owner = nullptr;
}

Player::Player(Collider& Body, float Speed, float Smooth)
	: m_Body(&Body)
	, Speed(Speed)
	, Smooth(Smooth)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(0.0f, 0.0f)
	, Score(0)
	, CanMove(false)
	, m_JumpCounter(0)
{
	Body.Owner = this;
}

Player::Player(Collider& Body, float Speed, float Smooth, sf::Vector2f Distance, float Time)
	: m_Body(&Body)
	, Speed(Speed)
	, Smooth(Smooth)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(0.0f, 0.0f)
	, Score(0)
	, CanMove(false)
	, isFalling(false)
	, m_Distance(Distance.x, Distance.y)
	, m_Time(Time * 0.5f)
	, m_JumpCounter(0)
{
	m_Acceleration.y = 2.0f * m_Distance.y / (m_Time * m_Time);
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

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && (!isFalling || m_JumpCounter < 2))
	{
		m_Acceleration.x = -2.0f * m_Distance.y * (m_Velocity.x * m_Velocity.x) / (m_Distance.x * m_Distance.x);
		m_Acceleration.y = 2.0f * m_Distance.y / (m_Time * m_Time);
		m_Velocity.x = 2.0f * m_Distance.y * m_Velocity.x / m_Distance.x;
		m_Velocity.y = -2.0f * m_Distance.y / m_Time;
		std::cout << "V0: " << m_Velocity.x << ", " << m_Velocity.y << std::endl;
		std::cout << "ACC: " << m_Acceleration.x << ", " << m_Acceleration.y << std::endl << std::endl;
		isFalling = true;
		m_JumpCounter++;
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

		m_Direction = Dir * Speed;
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		m_Direction = sf::Vector2f(0.0f, 0.0f);
	}
}

void Player::UpdatePosition(sf::Int32 DeltaTime)
{
	if (CanMove && !isFalling)
	{
		m_Velocity.x = m_Direction.x * (1.0f - Smooth) + m_Velocity.x * Smooth;
		m_Body->Body->setPosition(m_Body->Body->getPosition() + m_Velocity * (float)DeltaTime);
		m_Velocity.y = 0;
		m_JumpCounter = 0;
	}
	else if (isFalling)
	{
		Jump(DeltaTime);
	}
}

void Player::Jump(sf::Int32 DeltaTime)
{
	float dt = DeltaTime;
	getBodyShape()->setPosition(getBodyShape()->getPosition() + m_Velocity * dt + 0.5f * m_Acceleration * dt * dt);
	if (m_Velocity.y > 0.0f)
	{
		m_Velocity.y += m_Acceleration.y * dt * 4.0f;
	}
	else
	{
		m_Velocity.y += m_Acceleration.y * dt;
	}
}

void Player::SetJumpHeight(float Height)
{
	system("cls");
	std::cout << "Jump height changed from: " << m_Distance.y << " to: " << Height << std::endl;
	m_Distance.y = Height;
}

float Player::GetJumpHeight() const
{
	return m_Distance.y;
}

void Player::SetJumpDistance(float Distance)
{
	system("cls");
	std::cout << "Jump distance changed from: " << m_Distance.x << " to: " << Distance << std::endl;
	m_Distance.x = Distance;
}

float Player::GetJumpDistance() const
{
	return m_Distance.x;
}


Collider* Player::getBody() const
{
	return m_Body;
}

sf::Shape* Player::getBodyShape() const
{
	return m_Body->Body;
}


