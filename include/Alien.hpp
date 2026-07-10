#pragma once
#include "GameObject.hpp"

class Alien : public GameObject {
private:
    int pointValue;

public:
    Alien(sf::Texture* texture, sf::Vector2f startPos, int points);
    ~Alien();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void MoveDown(float distance);
    void MoveHorizontal(float distance); 
    int GetPoints() { return pointValue; }
};  