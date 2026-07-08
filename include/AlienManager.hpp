#pragma once
#include <vector>
#include "Alien.hpp"
#include "Bullet.hpp"

class AlienManager {
private:
    std::vector<Alien*> aliens;
    float moveSpeed;
    bool movingRight;

public:
    AlienManager();
    ~AlienManager();

    void InitializeSwarm(sf::Texture* alienTexture);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);
    
    void AlienShoot(std::vector<Bullet*>& bulletList, sf::Texture* bulletTexture);
    
    std::vector<Alien*>& GetAliens() { return aliens; }
};