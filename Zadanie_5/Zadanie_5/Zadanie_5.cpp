#include <SFML/Graphics.hpp>
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

    sf::Texture TexP1;
    TexP1.loadFromFile("Resources/Mario.png");
    TexP1.generateMipmap();
    sf::Sprite SpriteP1(TexP1);
    SpriteP1.setTextureRect(sf::IntRect(0, 0, 1500, 1500));
    SpriteP1.setScale(0.07f, 0.07f);
    SpriteP1.setOrigin(50.f, 50.f);
    SpriteP1.setPosition(200.f, 200.f);
    Player PlayerKeyboard = Player(&SpriteP1, 1.0f, 0.98f);

    sf::Texture TexP2;
    TexP2.loadFromFile("Resources/Luigi.png");
    TexP2.generateMipmap();
    sf::Sprite SpriteP2(TexP2);
    SpriteP2.setTextureRect(sf::IntRect(0, 0, 260, 480));
    SpriteP2.setScale(0.208f, 0.208f);
    SpriteP2.setOrigin(27.f, 50.f);
    SpriteP2.setPosition(100.f, 100.f);
    Player PlayerMouse = Player(&SpriteP2);
    PlayerMouse.Speed = 1.2f;

    Camera camera(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::FloatRect(0.0f, 0.0f, loader.Size.x, loader.Size.y));

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
            PlayerMouse.GetMouseInput(event, camera.View, window);
        }
        
        camera.UpdatePosition((PlayerKeyboard.getBody()->getPosition() + PlayerMouse.getBody()->getPosition()) / 2.0f);
        camera.UpdateSize(PlayerKeyboard.getBody()->getPosition(), PlayerMouse.getBody()->getPosition(), window);

        PlayerKeyboard.UpdatePosition(deltaTime.asMilliseconds());
        PlayerMouse.UpdatePosition(deltaTime.asMilliseconds());
        for (sf::Sprite s : loader.Elements)
        {
            window.draw(s);
        }
        // Draw objects
        window.draw(*PlayerKeyboard.getBody());
        window.draw(*PlayerMouse.getBody());
        window.setView(camera.View);

        window.display();
        // Setting Background
        window.clear(sf::Color::Blue);
        deltaTime = deltaClock.restart();
    }

    return 0;
}