#include "Buff.hpp"

Buff::Buff(sf::Texture* texture,
           sf::Vector2f startPos,
           BuffType buffType)
    : GameObject(texture)
{
    position = startPos;
    sprite.setPosition(position);

    type = buffType;
    fallSpeed = 120.0f;
}

Buff::~Buff()
{
}

void Buff::Update(float deltaTime)
{
    position.y += fallSpeed * deltaTime;

    sprite.setPosition(position);

    // Rơi khỏi màn hình thì xóa
    if (position.y > 920.0f)
    {
        Destroy();
    }
}

void Buff::Render(sf::RenderWindow& window)
{
    if (IsActive())
    {
        window.draw(sprite);
    }
}

BuffType Buff::GetType() const
{
    return type;
}