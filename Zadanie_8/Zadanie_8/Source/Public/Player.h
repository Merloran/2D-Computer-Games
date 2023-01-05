#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Player
{
public:
	Player(Collider& Body);

	Player(Collider& Body, float Speed, float Smooth);

	Player(Collider& Body, float Speed, float Smooth, sf::Vector2f Distance, float Time);

	virtual ~Player();

	/** Getting keybord input and set Speed on Direction */
	void GetMovementInput(sf::Event event);

	/** Getting mouse input and set Speed on Direction */
	void GetMouseInput(sf::Event even, sf::View CameraView, sf::RenderWindow& Window);

	/** Update position by keyboard input and Speed */
	void UpdatePosition(sf::Int32 DeltaTime);

	void Jump(sf::Int32 DeltaTime);

	void SetJumpHeight(float Height);
	float GetJumpHeight() const;

	void SetJumpDistance(float Distance);
	float GetJumpDistance() const;

	/** Body getter */
	Collider* getBody() const;
	sf::Shape* getBodyShape() const;

	/** Move speed parameter */
	float Speed;
	bool CanMove;
	bool isFalling;

	/** Move smooth parameter */
	float Smooth;

	unsigned int Score;

private:
	Collider* m_Body;

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;

	// Height in pixels
	sf::Vector2f m_Distance;
	// Time in miliseconds
	float m_Time;

	int m_JumpCounter;

	/** Direction from input based on Speed */
	sf::Vector2f m_Direction;
};

