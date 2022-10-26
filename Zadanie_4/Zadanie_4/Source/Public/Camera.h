#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	sf::View View;
	Camera(sf::Vector2f ViewSize, sf::FloatRect Border);
	
	void UpdatePosition(sf::Vector2f Target);


private:
	sf::FloatRect m_Border;
	sf::Vector2f m_Position;
};

