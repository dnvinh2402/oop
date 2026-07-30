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

    bool bombReady;
    float bombTimer;
    // ================


public:
    Player(sf::Texture *texture, sf::Vector2f startPos);
    ~Player();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow &window) override;

    void HandleInput();

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
    // ================

    int GetLives() { return lives; }
    int GetScore() { return score; }
    void AddScore(int points) { score += points; }
};