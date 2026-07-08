#pragma once
#include "GameObject.hpp"
#include "Bullet.hpp"
#include <vector>

class Player : public GameObject {
private:
    float speed;
    int lives;
    int score;
    float fireCooldown;
    float currentCooldown;

public:
    Player(sf::Texture* texture, sf::Vector2f startPos);
    ~Player();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void HandleInput();
    
    // Hàm bắn: Đẩy đạn mới (dùng toán tử new) vào mảng bulletList
    void Shoot(std::vector<Bullet*>& bulletList, sf::Texture* bulletTexture);
    void TakeDamage();

    int GetLives() { return lives; }
    int GetScore() { return score; }
    void AddScore(int points) { score += points; }
};