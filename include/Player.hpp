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

    int healthLevel;
    int fireRateLevel;
    int speedLevel;

    // ===== Buff =====
    bool doubleShot;
    bool shield;

    float doubleShotTimer;
    float shieldTimer;
    int shieldHitsRemaining; // Thêm biến đếm số lần chịu đạn (tối đa 2 lần)

    bool invincible;
    float invincibleTimer;
    float blinkTimer;
    bool blinkVisible;

    bool bombReady;
    float bombTimer;
    // ================

public:
    Player(sf::Texture *texture, sf::Vector2f startPos,
           int healthLevel,
           int fireRateLevel,
           int speedLevel);
    ~Player();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow &window) override;

    void HandleInput(float deltaTime);

    bool Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture);
    void TakeDamage();

    // ===== Buff =====
    void ActivateDoubleShot();
    void ActivateShield();
    void ActivateBomb();
    bool IsBombReady() const;
    void ResetBomb();
    int bombCount;

    bool HasShield() const;
    bool IsInvincible() const;
    void StartInvincibility(float duration);
    void TakeShieldHit();

    // Thêm 2 hàm này để lấy thông tin hiển thị lên UI
    float GetShieldTimer() const { return shieldTimer; }
    int GetShieldHitsRemaining() const { return shieldHitsRemaining; }
    float GetInvincibleTimer() const { return invincibleTimer; }
    float GetCurrentCooldown() const {return currentCooldown; }
    // ================

    float GetDoubleShotTimer() const { return doubleShotTimer; }

    bool HasDoubleShot() const { return doubleShot; }

    int GetLives() { return lives; }
    int GetScore() { return score; }
    void AddScore(int points) { score += points; }
};