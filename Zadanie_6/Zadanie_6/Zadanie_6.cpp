#include <SFML/Graphics.hpp>
#include "Source/Public/Collision.h"
#include <iostream>
#include <vector>

using namespace std;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FRAME_RATE_LIMIT 120

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_6");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    std::vector<Collision> colliders;
    int count = 30;
    colliders.reserve(count);

    srand(time(NULL));

    sf::Vector2f start = sf::Vector2f();
    sf::Vector2f vel = sf::Vector2f();
    float size;

    for (int i = 0; i < count; ++i)
    {
        start.x = (float)(rand() % WINDOW_WIDTH);
        start.y = (float)(rand() % WINDOW_HEIGHT);
        vel.x = (float)(rand() % 20 - 10);
        vel.y = (float)(rand() % 20 - 10);
        size = (float)(rand() % 40 + 10);
        colliders.push_back(Collision(start, size, 0.2f, vel));
    }

    bool IsReflecting = true;
    bool IsSeparating = true;

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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    IsSeparating ^= true;
                    std::cout << "Separation " << (IsSeparating ? "Enabled" : "Disabled") << std::endl;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    IsReflecting ^= true;
                    std::cout << "Reflection " << (IsReflecting ? "Enabled" : "Disabled") << std::endl;
                }
            }

        }

        for (int i = 0; i < count; ++i)
        {
            for (int j = i + 1; j < count; ++j)
            {
                Collision::CheckCollision(colliders[i], colliders[j], IsSeparating, IsReflecting);
            }
        }

        for (int i = 0; i < count; ++i)
        {
            colliders[i].Move(deltaTime.asMilliseconds());
        }

        window.display();
        // Setting Background
        window.clear(sf::Color::Blue);

        for (int i = 0; i < count; ++i)
        {
            window.draw(colliders[i].Body);
        }
        deltaTime = deltaClock.restart();
    }

    return 0;
}