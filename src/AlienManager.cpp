#include "AlienManager.hpp"
#include <cstdlib> // Thư viện hỗ trợ hàm rand() để random tỉ lệ nhả đạn
#include <iostream>
#include <cmath>

const float WORLD_WIDTH_HALF = 450.0f;
AlienManager::AlienManager() {
    moveSpeed = 100.0f; // Tốc độ di chuyển ngang (100 pixel/giây)
    movingRight = true; // Bầy quái bắt đầu đi từ trái sang phải
    currentRound = 1;
    maxRounds = 3;
}

AlienManager::~AlienManager() {
    // Dọn dẹp RAM: Xóa từng con quái khi tắt game
    for (Alien* alien : aliens) {
        delete alien;
    }
    aliens.clear();
}

void AlienManager::InitializeSwarm(sf::Texture* alienTexture) {
    if (currentRound == 1) {
        // ===== ROUND 1: Patrol - giống hệt bản gốc ban đầu =====
        int rows = 4;
        int cols = 8;
        float startX = 60.0f;
        float startY = 50.0f;
        float spacingX = 70.0f;
        float spacingY = 60.0f;

        int index = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                sf::Vector2f pos(startX + col * spacingX, startY + row * spacingY);
                int points = (rows - row) * 10;
                float delay = index * 0.05f;

                Alien* newAlien = new Alien(alienTexture, pos, 0.0f, 0.0f, delay, points, MovementType::Patrol, 1);
                aliens.push_back(newAlien);
                index++;
            }
        }
        moveSpeed = 100.0f;
        movingRight = true;
    }
    else if (currentRound == 2) {
        // ===== ROUND 2: Orbit - nhiều hơn, quay tròn =====
        int rows = 5;
        int cols = 9;
        float startX = 60.0f;
        float startY = 50.0f;
        float spacingX = 65.0f;
        float spacingY = 55.0f;

        float baseAngularSpeed = 1.3f;
        float staggerDelay = 0.1f;

        int index = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                sf::Vector2f center(startX + col * spacingX, startY + row * spacingY);
                float radius = 20.0f + (row % 3) * 10.0f;
                float speed = baseAngularSpeed + (rand() % 50) / 100.0f;
                float delay = index * staggerDelay;
                int points = (rows - row) * 10;

                Alien* newAlien = new Alien(alienTexture, center, radius, speed, delay, points, MovementType::Orbit, 1);
                aliens.push_back(newAlien);
                index++;
            }
        }
    }
    else {
        // ===== ROUND 3: Boss - 1 con duy nhất, nhiều máu =====
        sf::Vector2f bossCenter(WORLD_WIDTH_HALF, 150.0f);
        int bossHealth = 30;
        int bossPoints = 200;

        Alien* boss = new Alien(alienTexture, bossCenter, 250.0f, 0.6f, 0.0f, bossPoints, MovementType::Boss, bossHealth);
        aliens.push_back(boss);
    }

    std::cout << "Da khoi tao Round " << currentRound << " voi " << aliens.size() << " quai vat!\n";
}
void AlienManager::Update(float deltaTime) {
    if (aliens.empty()) return;

    if (currentRound == 1) {
        // Chỉ Round 1 (Patrol) cần logic di chuyển đồng bộ cả đàn
        float moveDistance = moveSpeed * deltaTime;
        if (!movingRight) moveDistance = -moveDistance;

        for (Alien* alien : aliens) {
            if (alien->IsActive()) {
                alien->MoveHorizontal(moveDistance);
            }
        }

        float minX = 9999.0f;
        float maxX = -9999.0f;
        bool hasActiveAliens = false;

        for (Alien* alien : aliens) {
            if (alien->IsActive()) {
                hasActiveAliens = true;
                sf::FloatRect bounds = alien->GetBounds();
                if (bounds.position.x < minX) minX = bounds.position.x;
                if (bounds.position.x + bounds.size.x > maxX) maxX = bounds.position.x + bounds.size.x;
            }
        }

        if (hasActiveAliens) {
            if (maxX > 900.0f) {
                float overshoot = maxX - 900.0f;
                for (Alien* alien : aliens) {
                    if (alien->IsActive()) alien->MoveHorizontal(-overshoot);
                }
                movingRight = false;
            } else if (minX < 0.0f) {
                float overshoot = 0.0f - minX;
                for (Alien* alien : aliens) {
                    if (alien->IsActive()) alien->MoveHorizontal(overshoot);
                }
                movingRight = true;
            }
        }
    }

    // Mọi round đều cần Update() riêng của từng Alien (spawn, cooldown, Orbit/Boss di chuyển)
    for (Alien* alien : aliens) {
        if (alien->IsActive()) {
            alien->Update(deltaTime);
        }
    }
}

void AlienManager::Render(sf::RenderWindow& window) {
    for (Alien* alien : aliens) {
        if (alien->IsActive()) {
            alien->Render(window);
        }
    }
}

void AlienManager::AlienShoot(std::vector<Bullet*>& bulletList, sf::Texture* bulletTexture) {
    // 1. Lọc danh sách quái còn sống
    std::vector<Alien*> activeAliens;
    for (Alien* alien : aliens) {
        if (alien->IsActive()) activeAliens.push_back(alien);
    }
    if (activeAliens.empty()) return;

    // 2. Đếm số lượng đạn quái đang bay trên màn hình
    int currentAlienBullets = 0;
    for (Bullet* b : bulletList) {
        if (!b->IsPlayerBullet() && b->IsActive()) {
            currentAlienBullets++;
        }
    }

    // Giới hạn cấp độ khó: Tối đa 6 viên đạn quái xuất hiện cùng lúc
    int maxBulletsAllowed = (currentRound == 3) ? 20 : (4 + currentRound);
    if (currentAlienBullets >= maxBulletsAllowed) return;
    
    // Duyệt qua từng con quái còn sống, con nào SẴN SÀNG (hết cooldown riêng) mới được bắn
    for (Alien* shooter : activeAliens) {
        if (currentAlienBullets >= maxBulletsAllowed) break;

        if (shooter->CanShoot()) {
            sf::FloatRect bounds = shooter->GetBounds();
            sf::Vector2f basePos;
            basePos.x = bounds.position.x + bounds.size.x / 2.0f - 5.0f;
            basePos.y = bounds.position.y + bounds.size.y;

            float bulletSpeed = 150.0f + (currentRound - 1) * 75.0f;

            if (shooter->GetMovementType() == MovementType::Boss){
                int bulletCount = 5;
                float spreadAngleDeg = 70.0f; // tổng góc toả ra
                for (int i = 0; i < bulletCount; i++){
                    float t = (bulletCount == 1) ? 0.5f : (float)i /(bulletCount - 1);
                    float angleDeg = -spreadAngleDeg / 2.0f + spreadAngleDeg * t;
                    float angleRad = angleDeg * 3.14159265f / 180.0f;


                    sf::Vector2f vel(std::sin(angleRad) * bulletSpeed, std::cos(angleRad) * bulletSpeed);

                    Bullet* newBullet = new Bullet(bulletTexture, basePos, vel, false);
                    bulletList.push_back(newBullet);
                    currentAlienBullets++;
                }
            }

            else{
                float bulletSpeed = 150.0f + (currentRound - 1) * 75.0f;
                sf::Vector2f bulletVel(0.0f, bulletSpeed);

                Bullet* newBullet = new Bullet(bulletTexture, basePos, bulletVel, false);
                bulletList.push_back(newBullet);

                currentAlienBullets++;
            }
            shooter->ResetShootCooldown();
        }
    }
}

bool AlienManager::IsRoundCleared() {
    // Nếu danh sách rỗng hoặc mọi con đều không còn active -> round đã bị tiêu diệt hết
    for (Alien* alien : aliens) {
        if (alien->IsActive()) return false;
    }
    return true;
}

bool AlienManager::IsFinalRound() {
    return currentRound >= maxRounds;
}

void AlienManager::StartNextRound(sf::Texture* alienTexture) {
    // Dọn sạch danh sách quái cũ đã chết (giải phóng bộ nhớ)
    for (Alien* alien : aliens) {
        delete alien;
    }
    aliens.clear();

    currentRound++;
    InitializeSwarm(alienTexture);
}

void AlienManager::Reset(sf::Texture* alienTexture){
    for (Alien* alien : aliens){
        delete alien;
    }

    aliens.clear();

    currentRound = 1;
    moveSpeed = 100.0f;
    movingRight = true;

    InitializeSwarm(alienTexture);
}