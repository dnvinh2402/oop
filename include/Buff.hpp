#pragma once

#include "GameObject.hpp"
enum class BuffType
{
    doubleShot,
    Shield,
    Bomb
};

class Buff : public GameObject
{
private:
    BuffType type;
    float fallSpeed;

public:
    Buff(sf::Texture* texture,
         sf::Vector2f startPos,
         BuffType buffType);

    ~Buff();

    void Update(float deltaTime) override;

    void Render(sf::RenderWindow& window) override;

    BuffType GetType() const;
};