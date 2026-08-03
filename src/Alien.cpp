#include "Alien.hpp"
#include <cmath>

const float WORLD_W = 900.0f;
const float WORLD_H = 900.0f;

Alien::Alien(sf::Texture* texture, sf::Vector2f orbitCenterPos, float radius, float speed, float delay, int points, MovementType type, int hp)
    : GameObject(texture) {

    orbitCenter = orbitCenterPos;
    orbitRadius = radius;
    angularSpeed = speed;
    angle = 0.0f;
    pointValue = points;

    spawnDelay = delay;
    spawnTimer = 0.0f;
    hasSpawned = false;
    aliveTimer = 0.0f;
    survivalTime = 0.0f; // Khởi tạo thời gian sống ban đầu bằng 0
    movementType = type;
    
    maxHealth = hp;
    currentHealth = hp;

    entryStartPos = sf::Vector2f(orbitCenter.x, -60.0f);
    position = entryStartPos;
    sprite.setPosition(position);

    shootCooldown = 2.0f + (rand() % 300) / 100.0f;
    shootTimer = (rand() % 200) / 100.0f;


    sprite.setPosition(position);
}

Alien::~Alien() {
}

void Alien::Update(float deltaTime) {
    if (!hasSpawned) {
        spawnTimer += deltaTime;
        if (spawnTimer < spawnDelay) {
            return;
        }
        hasSpawned = true;
        aliveTimer = 0.0f;
    }
    else {
        aliveTimer += deltaTime;
        survivalTime += deltaTime; // Tăng dần thời gian tồn tại sau khi xuất hiện để tính điểm tốc độ
        if (shootTimer > 0.0f) shootTimer -= deltaTime;
    }

    if (movementType == MovementType::Patrol) {
        static const float ENTRY_DURATION = 1.0f;
        if (aliveTimer < ENTRY_DURATION) {
            float t = aliveTimer / ENTRY_DURATION;
            position.y = entryStartPos.y + (orbitCenter.y - entryStartPos.y) * t;
        } else {
            position.y = orbitCenter.y;
        }
        sprite.setPosition(position);
        return;
    }

    if (movementType == MovementType::Boss) {
        static const float ENTRY_DURATION = 1.5f;
        angle += angularSpeed * deltaTime;

        float targetX = orbitCenter.x + std::sin(angle) * orbitRadius;
        float targetY = orbitCenter.y;

        float margin = 80.0f;
        if (targetX < margin) targetX = margin;
        if (targetX > WORLD_W - margin) targetX = WORLD_W - margin;

        if (aliveTimer < ENTRY_DURATION) {
            float t = aliveTimer / ENTRY_DURATION;
            position.x = entryStartPos.x + (targetX - entryStartPos.x) * t;
            position.y = entryStartPos.y + (targetY - entryStartPos.y) * t;
        } else {
            position.x = targetX;
            position.y = targetY;
        }
        sprite.setPosition(position);
        return;
    }

    angle += angularSpeed * deltaTime;

    float targetX = orbitCenter.x + std::cos(angle) * orbitRadius;
    float targetY = orbitCenter.y + std::sin(angle) * orbitRadius;

    static const float ENTRY_DURATION = 1.0f;

    if (aliveTimer < ENTRY_DURATION) {
        float t = aliveTimer / ENTRY_DURATION;
        position.x = entryStartPos.x + (targetX - entryStartPos.x) * t;
        position.y = entryStartPos.y + (targetY - entryStartPos.y) * t;
    } else {
        position.x = targetX;
        position.y = targetY;
    }

    if (position.x < -40.0f) position.x = WORLD_W + 40.0f;
    if (position.x > WORLD_W + 40.0f) position.x = -40.0f;
    if (position.y < -40.0f) position.y = WORLD_H + 40.0f;
    if (position.y > WORLD_H + 40.0f) position.y = -40.0f;

    sprite.setPosition(position);
}

void Alien::Render(sf::RenderWindow& window) {
    if (!hasSpawned && spawnTimer < spawnDelay) return;
    window.draw(sprite);
}

void Alien::MoveDown(float distance) {
    position.y += distance;
    sprite.setPosition(position);
}

void Alien::MoveHorizontal(float distance) {
    position.x += distance;
    sprite.setPosition(position);
}

bool Alien::CanShoot() {
    return hasSpawned && shootTimer <= 0.0f;
}

void Alien::ResetShootCooldown() {
    shootTimer = shootCooldown;
}

void Alien::TakeDamage(int amount){
    currentHealth -= amount;
    if (currentHealth <= 0) {
        Destroy();
    }
}