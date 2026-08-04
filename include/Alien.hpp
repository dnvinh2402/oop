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
    float survivalTime; // Thời gian sống sót (dùng cho cả lính thường lẫn Boss)

    sf::Vector2f entryStartPos; 

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

    void AddSurvivalTime(float dt) { survivalTime += dt; }

    // Hàm tính điểm riêng cho Boss màn 3 theo yêu cầu
    int CalculateBossHitScore() const {
        // Mỗi lần bắn trúng Boss: 200 điểm, giảm dần theo thời gian, thấp nhất 30 điểm
        float bonus = 200.0f - (survivalTime * 5.0f); 
        if (bonus < 30.0f) {
            bonus = 30.0f;
        }
        return (int)bonus;
    }

    int CalculateBossKillScore() const {
        // Khi tiêu diệt hoàn toàn Boss: cộng thêm 1000 điểm
        return 1000;
    }

    // Hàm tính điểm cho lính thường (giữ nguyên quy luật cũ: 100đ giảm dần, thấp nhất 10đ)
    int CalculateNormalScore() const {
        int baseScore = pointValue;
        float bonus = 100.0f - (survivalTime * 5.0f); 
        if (bonus < 10.0f) {
            bonus = 10.0f; 
        }
        return baseScore + (int)bonus;
    }

    MovementType GetMovementType() { return movementType; }
};