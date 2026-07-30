#pragma once
#include "GameObject.hpp"
enum class MovementType {
    Patrol, Orbit, Boss
};

class Alien : public GameObject {
private:
    int pointValue;

    MovementType movementType;

    sf::Vector2f orbitCenter;
    float orbitRadius;
    float angle;
    float angularSpeed;

    float spawnDelay;
    float spawnTimer;
    bool hasSpawned;
    float aliveTimer;

    sf::Vector2f entryStartPos; // vị trí bắt đầu bay vào (ngoài màn hình)

    float shootCooldown;
    float shootTimer;
    
    int maxHealth;
    int currentHealth;

public:
    Alien(sf::Texture* texture, sf::Vector2f orbitCenterPos, float radius, float speed, float delay, int points, MovementType type = MovementType::Orbit, int hp  = 1);
    ~Alien();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void MoveDown(float distance);
    void MoveHorizontal(float distance); 
    int GetPoints() { return pointValue; }

    bool CanShoot();  
    void ResetShootCooldown();

    void TakeDamage(int amount);
    int GetHealth() {return currentHealth; }
    int GetMaxHealth() {return maxHealth; }
};  