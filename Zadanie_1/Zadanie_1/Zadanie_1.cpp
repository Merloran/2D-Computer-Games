#include <SFML/Graphics.hpp>
#include "Source/Public/Object.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FRAME_RATE_LIMIT 60


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_1");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    // Setting Stone object
    Object Stone = Object("./Resources/StoneTexture.jpg", sf::IntRect(0, 0, 100, 100), sf::Vector2f(3.f, 3.f));
    Stone.SetPosition(200.f, 100.f);

    // Setting Ice object
    Object Ice = Object("./Resources/IceTexture.jpg");

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
        }
        if (Stone.GetX() + Stone.GetWidth() >= window.getSize().x && Stone.Velocity.x > 0.f || 
            Stone.GetX() <= 0.f && Stone.Velocity.x < 0.f)
        {
            Stone.Velocity.x *= -1;
        }

        if (Stone.GetY() + Stone.GetHeight() >= window.getSize().y && Stone.Velocity.y > 0.f ||
            Stone.GetY() <= 0.f && Stone.Velocity.y < 0.f)
        {
            Stone.Velocity.y *= -1;
        }

        // Setting Backgroud
        window.clear(sf::Color::Blue);
        // Draw objects
        window.draw(Stone.GetSprite());
        window.draw(Ice.GetSprite());
        window.display();

        // Change position
        Stone.UpdatePostion();
    }

    return 0;
}