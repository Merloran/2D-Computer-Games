#include "../../Source/Public/Object.h"

Object::Object()
    : Velocity(0.f, 0.f)
{
}

Object::Object(const char* Path, sf::IntRect Area, sf::Vector2f Velocity)
    : Velocity(Velocity)
{
    Texture.loadFromFile(Path);
    Sprite = sf::Sprite(Texture);
    Sprite.setTextureRect(Area);
}

void Object::UpdatePostion()
{
    Sprite.setPosition(Sprite.getPosition().x + Velocity.x, Sprite.getPosition().y + Velocity.y);
}

sf::Sprite Object::GetSprite()
{
    return Sprite;
}