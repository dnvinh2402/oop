#pragma once
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"
#include <vector>

class Player : public GameObject
{
private:
    float speed;
    int lives;
    int score;

    float fireCooldown;
    float currentCooldown;

    // ===== Buff =====
    bool doubleShot;
    bool shield;

    sf::Texture* shieldTexture;

    float doubleShotTimer;
    float shieldTimer;
    int shieldHitsRemaining; // Thêm biến đếm số lần chịu đạn (tối đa 2 lần)

    bool bombReady;
    float bombTimer;
    // ================

public:
    Player(sf::Texture *texture, sf::Vector2f startPos);
    ~Player();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow &window) override;

    void HandleInput(float deltaTime);

    void Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture);
    void TakeDamage();

    // ===== Buff =====
    void ActivateDoubleShot();
    void ActivateShield();
    void ActivateBomb();
    bool IsBombReady() const;
    void ResetBomb();

    void SetShieldTexture(sf::Texture* texture);

    bool HasShield() const;
    void TakeShieldHit(); // Hàm xử lý khi khiên hứng đạn
    
    // Thêm 2 hàm này để lấy thông tin hiển thị lên UI
    float GetShieldTimer() const { return shieldTimer; }
    int GetShieldHitsRemaining() const { return shieldHitsRemaining; }
    // ================

    int GetLives() { return lives; }
    int GetScore() { return score; }
    void AddScore(int points) { score += points; }
};