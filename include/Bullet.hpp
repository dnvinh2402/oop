#pragma once
#include "GameObject.hpp"

class Bullet : public GameObject {
private:
    sf::Vector2f velocity;
    bool isPlayerBullet;

public:
    Bullet(sf::Texture* texture, sf::Vector2f startPos, sf::Vector2f vel, bool isPlayer);
    ~Bullet();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    bool IsPlayerBullet() { return isPlayerBullet; }
};