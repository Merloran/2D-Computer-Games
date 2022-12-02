#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
class Player
{
public:
	Player(Collision& Body);

	Player(Collision& Body, float Speed, float Smooth);

	virtual ~Player();

	/** Getting keybord input and set Speed on Direction */
	void GetMovementInput(sf::Event event);

	/** Getting mouse input and set Speed on Direction */
	void GetMouseInput(sf::Event even, sf::View CameraView, sf::RenderWindow& Window);

	/** Update position by keyboard input and Speed */
	void UpdatePosition(sf::Int32 DeltaTime);


	/** Body getter */
	Collision* getBody() const;
	sf::Shape* getBodyShape() const;

	/** Move speed parameter */
	float Speed;
	bool CanMove;

	/** Move smooth parameter */
	float Smooth;

	unsigned int Score;

private:
	Collision* m_Body;

	sf::Vector2f m_Velocity;

	/** Direction from input based on Speed */
	sf::Vector2f m_Direction;
};

