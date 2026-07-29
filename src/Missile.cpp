#include "Missile.hpp"

Missile::Missile(sf::Texture* texture,
                 sf::Vector2f startPos)
    : GameObject(texture)
{
    position = startPos;
    sprite.setPosition(position);

    velocity.x = 0.f;
    velocity.y = -350.f;
}

Missile::~Missile()
{
}

void Missile::Update(float deltaTime)
{
    position += velocity * deltaTime;

    sprite.setPosition(position);

    if(position.y < -50.f)
    {
        Destroy();
    }
}

void Missile::Render(sf::RenderWindow& window)
{
    if(IsActive())
    {
        window.draw(sprite);
    }
}