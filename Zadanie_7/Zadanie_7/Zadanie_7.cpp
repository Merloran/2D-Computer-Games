#include <SFML/Graphics.hpp>
#include "Source/Public/Player.h"
#include "Source/Public/Collision.h"
#include "Source/Public/MapLoader.h"
#include "Source/Public/Camera.h"
#include <iostream>
#include <fstream>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define FRAME_RATE_LIMIT 120
#define LEVEL_COUNT 3

void LoadMap(MapLoader& Map)
{
    Map.SetDefaultTile("Resources/road.png");
    Map.AddTile("Resources/dot.png", '.');
    Map.AddTile("Resources/hash.png", '#', true);
    Map.AddTile("Resources/door.png", '=');
    Map.AddTile("Resources/wall_h.png", '-', true);
    Map.AddTile("Resources/wall_v.png", '|', true);
    Map.AddTile("Resources/wall_right_d.png", '\\', true);
    Map.AddTile("Resources/wall_rightUp_d.png", '`', true);
    Map.AddTile("Resources/wall_left_d.png", '/', true);
    Map.AddTile("Resources/wall_leftUp_d.png", '\'', true);
    Map.CreateObjects();
    Map.IsMapLoaded = true;
}

void Delay(sf::Time Seconds)
{
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < Seconds.asSeconds());
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_4");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    MapLoader Levels[LEVEL_COUNT] =
    {
        MapLoader("Resources/level1.txt", 100.0f),
        MapLoader("Resources/level2.txt", 100.0f),
        MapLoader("Resources/level3.txt", 100.0f),
    };
    int Current = 0;
    LoadMap(Levels[0]);

    sf::Vertex line1[] = 
    {
        {sf::Vector2f(0.0f, 0.0f), sf::Color::Black},
        {sf::Vector2f(0.0f, 0.0f), sf::Color::White} 
    };

    sf::Vertex line2[] = 
    {
        {sf::Vector2f(0.0f, 0.0f), sf::Color::Black},
        {sf::Vector2f(0.0f, 0.0f), sf::Color::White} 
    };

    Collision C1(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(100.0f, 100.0f));
    Collision C2(sf::Vector2f(200.0f, 100.0f), 50.0f);
    Player PlayerMouse = Player(C1, 1.3f, 0.98f);
    Player PlayerKeyboard = Player(C2, 1.2f, 0.98f);

    Camera camera(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::FloatRect(0.0f, 0.0f, Levels[0].Size.x, Levels[0].Size.y));

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

        PlayerKeyboard.UpdatePosition(deltaTime.asMilliseconds());
        PlayerMouse.UpdatePosition(deltaTime.asMilliseconds());

        for (int i = 0; i < LEVEL_COUNT; ++i)
        {
            if (Levels[i].IsMapLoaded)
            {
                if (Levels[i].CheckColliders(PlayerKeyboard) || Levels[i].CheckColliders(PlayerMouse))
                {
                    Current = (i + 1) % LEVEL_COUNT;
                    Levels[i].ClearMap();
                    LoadMap(Levels[Current]);
                    camera.SetBorder(sf::FloatRect(0.0f, 0.0f, Levels[Current].Size.x, Levels[Current].Size.y));
                    if (Current == 0)
                    {
                        std::cout << "P1: " << PlayerKeyboard.Score << std::endl;
                        std::cout << "P2: " << PlayerMouse.Score << std::endl;
                        std::cout << "***" << (PlayerKeyboard.Score > PlayerMouse.Score ? "P1" : "P2") << " IS WINNER!***" << std::endl;
                        PlayerKeyboard.Score = 0;
                        PlayerMouse.Score = 0;
                    }
                    PlayerKeyboard.CanMove = false;
                    PlayerMouse.CanMove = false;
                    PlayerKeyboard.getBodyShape()->setPosition(Levels[Current].P1Start);
                    PlayerMouse.getBodyShape()->setPosition(Levels[Current].P2Start);
                    Delay(sf::seconds(1.0f));
                    deltaClock.restart();
                }
                else
                {
                    line1[0].position = PlayerKeyboard.getBodyShape()->getPosition();
                    line1[1].position = Levels[i].Exit;
                    line2[0].position = PlayerMouse.getBodyShape()->getPosition();
                    line2[1].position = Levels[i].Exit;
                    PlayerKeyboard.CanMove = true;
                    PlayerMouse.CanMove = true;
                }
                break;
            }
        }

        camera.UpdatePosition((PlayerKeyboard.getBodyShape()->getPosition() + PlayerMouse.getBodyShape()->getPosition()) * 0.5f);
        camera.UpdateSize(PlayerKeyboard.getBodyShape()->getPosition(), PlayerMouse.getBodyShape()->getPosition(), window);

        for (int i = 0; i < LEVEL_COUNT; ++i)
        {
            if (Levels[i].IsMapLoaded)
            {
                for (sf::Sprite& s : Levels[i].Elements)
                {
                    window.draw(s);
                }
                break;
            }
        }

        // Draw objects
        window.draw(*PlayerKeyboard.getBodyShape());
        window.draw(*PlayerMouse.getBodyShape());

        if (!camera.IsVisible(Levels[Current].Exit))
        {
            window.draw(line1, 2, sf::Lines);
            window.draw(line2, 2, sf::Lines);
        }

        window.setView(camera.View);

        window.display();
        // Setting Background
        window.clear(sf::Color::Cyan);
        deltaTime = deltaClock.restart();
    }

    return 0;
}