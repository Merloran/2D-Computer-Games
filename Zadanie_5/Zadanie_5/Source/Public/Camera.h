#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	sf::View View;

	Camera(sf::Vector2f ViewSize, sf::FloatRect Border);
	
	void UpdatePosition(sf::Vector2f Target);
	void UpdateSize(sf::Vector2f Target1, sf::Vector2f Target2, sf::RenderWindow& Window);

private:
	sf::FloatRect m_Border;
	sf::Vector2f m_Position;
};

