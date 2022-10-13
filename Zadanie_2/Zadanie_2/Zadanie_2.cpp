#include <SFML/Graphics.hpp>
#include "Source/Public/Player.h"
#include <iostream>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FRAME_RATE_LIMIT 120

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_2");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    sf::RectangleShape RectangleBody = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
    RectangleBody.setFillColor(sf::Color(100, 255, 100));
    RectangleBody.setPosition(100.f, 100.f);
    Player PlayerKeyboard = Player(&RectangleBody, 1.0f, 0.98f);

    sf::CircleShape CircleBody(40.f);
    CircleBody.setOrigin(40.f, 40.f);
    CircleBody.setFillColor(sf::Color(255, 0, 0, 128));
    Player PlayerMouse = Player(&CircleBody);

    sf::Clock deltaClock;
    sf::Time deltaTime;
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            PlayerKeyboard.GetMovementInput(event);
            PlayerMouse.UpdatePositionByMouse(event);
        }

        PlayerKeyboard.UpdatePosition(deltaTime.asMilliseconds());
        // Setting Backgroud
        window.clear(sf::Color::Blue);
        // Draw objects
        window.draw(*PlayerKeyboard.getBody());
        window.draw(*PlayerMouse.getBody());
        window.display();
        deltaTime = deltaClock.restart();
    }

    return 0;
}