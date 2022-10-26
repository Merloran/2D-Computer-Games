﻿#include <SFML/Graphics.hpp>
#include "Source/Public/Player.h"
#include "Source/Public/MapLoader.h"
#include "Source/Public/Camera.h"
#include <iostream>
#include <fstream>

using namespace std;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FRAME_RATE_LIMIT 120

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_4");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    MapLoader loader("Resources/map.txt", 100.0f);

    loader.SetDefaultTile("Resources/road.png");
    loader.AddTile("Resources/dot.png", '.');
    loader.AddTile("Resources/hash.png", '#');
    loader.AddTile("Resources/door.png", '=');
    loader.AddTile("Resources/wall_h.png", '-');
    loader.AddTile("Resources/wall_v.png", '|');
    loader.AddTile("Resources/wall_right_d.png", '\\');
    loader.AddTile("Resources/wall_rightUp_d.png", '`');
    loader.AddTile("Resources/wall_left_d.png", '/');
    loader.AddTile("Resources/wall_leftUp_d.png", '\'');
    loader.CreateObjects();

    sf::RectangleShape RectangleBody = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
    RectangleBody.setFillColor(sf::Color(100, 255, 100));
    RectangleBody.setPosition(100.f, 100.f);
    RectangleBody.setOrigin(50.f, 50.f);
    Player PlayerKeyboard = Player(&RectangleBody, 1.0f, 0.98f);

    sf::CircleShape CircleBody(40.f);
    CircleBody.setOrigin(40.f, 40.f);
    CircleBody.setFillColor(sf::Color(255, 0, 0, 128));
    Player PlayerMouse = Player(&CircleBody);

    Camera camera(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT),sf::FloatRect(0.0f, 0.0f, loader.Size.x, loader.Size.y));

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
        camera.UpdatePosition(PlayerKeyboard.getBody()->getPosition());

        PlayerKeyboard.UpdatePosition(deltaTime.asMilliseconds());
        // Setting Background
        window.clear(sf::Color::Blue);
        for (sf::Sprite s : loader.Elements)
        {
            window.draw(s);
        }
        // Draw objects
        window.draw(*PlayerKeyboard.getBody());
        window.draw(*PlayerMouse.getBody());
        window.display();
        window.setView(camera.View);
        deltaTime = deltaClock.restart();
    }

    return 0;
}