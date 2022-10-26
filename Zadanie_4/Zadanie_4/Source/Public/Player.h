#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Shape* Body);

	Player(sf::Shape* Body, float Speed, float Smooth);

	virtual ~Player();

	/** Getting keybord input and set Speed on Direction*/
	void GetMovementInput(sf::Event event);

	/** Update position by keyboard input and Speed */
	void UpdatePosition(sf::Int32 DeltaTime);

	/** Setting body position on mouse position */
	void UpdatePositionByMouse(sf::Event event);

	/** Body getter */
	sf::Shape* getBody() const;

	/** Move speed parameter */
	float Speed;

	/** Move smooth parameter */
	float Smooth;

private:
	sf::Shape* Body;

	sf::Vector2f Velocity;

	/** Direction from input based on Speed */
	sf::Vector2f Direction;
};

