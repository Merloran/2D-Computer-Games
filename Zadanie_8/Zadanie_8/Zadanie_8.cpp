#include <SFML/Graphics.hpp>
#include "Source/Public/Player.h"
#include "Source/Public/Collider.h"
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Zadanie_7");
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

    Collider C1(Levels[0].P1Start, sf::Vector2f(100.0f, 100.0f));
    Collider C2(Levels[0].P2Start, 50.0f);
    Player PlayerKeyboard = Player(C2, 1.2f, 0.89f, {400.0f, 200.0f}, 640.0f);

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
                if (event.key.code == sf::Keyboard::C)
                {
                    PlayerKeyboard.SetJumpDistance(PlayerKeyboard.GetJumpDistance() + 10.0f);
                }
                else if (event.key.code == sf::Keyboard::V)
                {
                    PlayerKeyboard.SetJumpDistance(PlayerKeyboard.GetJumpDistance() - 10.0f);
                }
                if (event.key.code == sf::Keyboard::B)
                {
                    PlayerKeyboard.SetJumpHeight(PlayerKeyboard.GetJumpHeight() + 10.0f);
                }
                else if (event.key.code == sf::Keyboard::N)
                {
                    PlayerKeyboard.SetJumpHeight(PlayerKeyboard.GetJumpHeight() - 10.0f);
                }
            }

            PlayerKeyboard.GetMovementInput(event);
        }

        if (deltaTime.asMilliseconds() > 30)
        {
            deltaTime = sf::milliseconds(30);
        }


        PlayerKeyboard.UpdatePosition(deltaTime.asMilliseconds());

        for (int i = 0; i < LEVEL_COUNT; ++i)
        {
            if (Levels[i].IsMapLoaded)
            {
                Tile* tile = Levels[i].CheckColliders(PlayerKeyboard);
                if (tile && tile->Character == '#')
                {
                    Current = (i + 1) % LEVEL_COUNT;
                    Levels[i].ClearMap();
                    LoadMap(Levels[Current]);
                    PlayerKeyboard.CanMove = false;
                    PlayerKeyboard.getBodyShape()->setPosition(Levels[Current].P1Start);
                    camera.SetBorder(sf::FloatRect(0.0f, 0.0f, Levels[Current].Size.x, Levels[Current].Size.y));


                    if (Current == 0)
                    {
                        std::cout << "SCORE!: " << PlayerKeyboard.Score << std::endl;
                        std::cout << "***YOU WIN!***" << std::endl;
                        PlayerKeyboard.Score = 0;
                    }

                    Delay(sf::seconds(1.0f));
                    deltaClock.restart();
                }
                else
                {
                    line1[0].position = PlayerKeyboard.getBodyShape()->getPosition();
                    line1[1].position = Levels[i].Exit;
                    PlayerKeyboard.CanMove = true;
                }
                break;
            }
        }

        camera.UpdatePosition((PlayerKeyboard.getBodyShape()->getPosition() + PlayerKeyboard.getBodyShape()->getPosition()) * 0.5f);
        camera.UpdateSize(PlayerKeyboard.getBodyShape()->getPosition(), PlayerKeyboard.getBodyShape()->getPosition(), window);

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

        if (!camera.IsVisible(Levels[Current].Exit))
        {
            window.draw(line1, 2, sf::Lines);
        }

        window.setView(camera.View);

        window.display();
        // Setting Background
        window.clear(sf::Color::Cyan);
        deltaTime = deltaClock.restart();
    }

    return 0;
}