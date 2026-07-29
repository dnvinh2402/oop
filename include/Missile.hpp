#pragma once

#include "GameObject.hpp"

class Missile : public GameObject
{
private:
    sf::Vector2f velocity;

public:
    Missile(sf::Texture* texture,
            sf::Vector2f startPos);

    ~Missile();

    void Update(float deltaTime) override;

    void Render(sf::RenderWindow& window) override;
};