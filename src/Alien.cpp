#include "Alien.hpp"
#include <cmath>

const float WORLD_W = 900.0f;
const float WORLD_H = 900.0f;

Alien::Alien(sf::Texture* texture, sf::Vector2f orbitCenterPos, float radius, float speed, float delay, int points)
    : GameObject(texture) {
    // position = startPos;
    // sprite.setPosition(position);
    // pointValue = points;

    orbitCenter = orbitCenterPos;
    orbitRadius = radius;
    angularSpeed = speed;
    angle = 0.0f;
    pointValue = points;

    spawnDelay = delay;
    spawnTimer = 0.0f;
    hasSpawned = false;
    aliveTimer = 0.0f;

    // Alien bắt đầu từ phía trên, ngoài màn hình
    entryStartPos = sf::Vector2f(orbitCenter.x, -60.0f);
    position = entryStartPos;
    sprite.setPosition(position);

    //Thoi gian ban
    shootCooldown = 2.0f + (rand() % 300) / 100.0f; // mỗi con có thời gian hồi chiêu riêng, 2-5s
    shootTimer = (rand() % 200) / 100.0f; // lệch pha ban đầu, tránh cả đàn bắn cùng lúc
}

Alien::~Alien() {
    // Chưa cần dọn gì đặc biệt
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
    else{
        aliveTimer += deltaTime;
        if (shootTimer > 0.0f) shootTimer -= deltaTime;
    }

    // Sau khi được kích hoạt: bay theo quỹ đạo tròn quanh orbitCenter
    angle += angularSpeed * deltaTime;

    float targetX = orbitCenter.x + std::cos(angle) * orbitRadius;
    float targetY = orbitCenter.y + std::sin(angle) * orbitRadius;

    // Giai đoạn "bay vào": nội suy mượt từ entryStartPos tới vị trí quỹ đạo đầu tiên
    // (đơn giản hóa: cho phép nó tự "rơi" dần vào quỹ đạo trong 1 giây đầu)
    static const float ENTRY_DURATION = 1.0f;

    if (aliveTimer < ENTRY_DURATION) {
        float t = aliveTimer / ENTRY_DURATION; // 0 -> 1
        position.x = entryStartPos.x + (targetX - entryStartPos.x) * t;
        position.y = entryStartPos.y + (targetY - entryStartPos.y) * t;
    } else {
        position.x = targetX;
        position.y = targetY;
    }

    // Screen wrap: nếu ra ngoài biên, dịch sang phía đối diện thay vì biến mất
    if (position.x < -40.0f) position.x = WORLD_W + 40.0f;
    if (position.x > WORLD_W + 40.0f) position.x = -40.0f;
    if (position.y < -40.0f) position.y = WORLD_H + 40.0f;
    if (position.y > WORLD_H + 40.0f) position.y = -40.0f;

    sprite.setPosition(position);
}

void Alien::Render(sf::RenderWindow& window) {
    if (!hasSpawned && spawnTimer < spawnDelay) return; // chưa xuất hiện -> không vẽ
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