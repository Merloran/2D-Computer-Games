#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Sprite* Body);

	Player(sf::Sprite* Body, float Speed, float Smooth);

	virtual ~Player();

	/** Getting keybord input and set Speed on Direction */
	void GetMovementInput(sf::Event event);

	/** Getting mouse input and set Speed on Direction */
	void GetMouseInput(sf::Event even, sf::View CameraView, sf::RenderWindow& Window);

	/** Update position by keyboard input and Speed */
	void UpdatePosition(sf::Int32 DeltaTime);


	/** Body getter */
	sf::Sprite* getBody() const;

	/** Move speed parameter */
	float Speed;

	/** Move smooth parameter */
	float Smooth;

private:
	sf::Sprite* m_Body;

	sf::Vector2f m_Velocity;

	/** Direction from input based on Speed */
	sf::Vector2f m_Direction;
};

