#include "AlienManager.hpp"
#include <cstdlib> // Thư viện hỗ trợ hàm rand() để random tỉ lệ nhả đạn
#include <iostream>

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
    // Cấu hình mạng lưới quái vật: 4 hàng x 8 cột
    int rows = 2 + currentRound;
    int cols = 8;
    float startX = 60.0f;
    float startY = 50.0f;
    float spacingX = 70.0f;
    float spacingY = 60.0f;

    float baseAngularSpeed = 1.0f + (currentRound - 1) * 0.3f; // round sau quay nhanh hơn
    float staggerDelay = 0.15f; // mỗi con cách nhau 0.15s xuất hiện

    int index = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            sf::Vector2f center(startX + col * spacingX, startY + row * spacingY);
            
            float radius = 20.0f + (row % 3) * 10.0f; // bán kính khác nhau theo hàng, tạo cảm giác đa dạng
            float speed = baseAngularSpeed + (rand() % 50) / 100.0f; // mỗi con tốc độ hơi khác nhau
            float delay = index * staggerDelay;
            int points = (rows - row) * 10;//diem tieu diet

            
            Alien* newAlien = new Alien(alienTexture, center, radius, speed, delay, points);
            aliens.push_back(newAlien);
            index++;
        }
    }

    moveSpeed = 100.0f + (currentRound - 1) * 30.0f;
    movingRight = true;


    std::cout << "Da khoi tao Round " << currentRound << " voi " << rows << " hang quai vat!\n";
}
void AlienManager::Update(float deltaTime) {
    if (aliens.empty()) return;

    // 1. Tính toán quãng đường di chuyển trong frame hiện tại
    float moveDistance = moveSpeed * deltaTime;
    if (!movingRight) moveDistance = -moveDistance;

    // 2. Di chuyển toàn bộ bầy (Chưa cần quan tâm va chạm)
    for (Alien* alien : aliens) {
        if (alien->IsActive()) {
            alien->MoveHorizontal(moveDistance);
        }
    }

    // 3. Quét tọa độ thực tế của bầy SAU KHI di chuyển
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

    if (!hasActiveAliens) return;

    // 4. Sửa lỗi lọt viền (Overshoot Correction)
    if (maxX > 800.0f) {
        float overshoot = maxX - 800.0f;
        for (Alien* alien : aliens) {
            if (alien->IsActive()) alien->MoveHorizontal(-overshoot);
        }
        movingRight = false; // Đảo chiều cho frame sau
    } else if (minX < 0.0f) {
        float overshoot = 0.0f - minX;
        for (Alien* alien : aliens) {
            if (alien->IsActive()) alien->MoveHorizontal(overshoot);
        }
        movingRight = true;
    }
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
    int maxBulletsAllowed = 4 + currentRound; 
    if (currentAlienBullets >= maxBulletsAllowed) return;
    
    // Duyệt qua từng con quái còn sống, con nào SẴN SÀNG (hết cooldown riêng) mới được bắn
    for (Alien* shooter : activeAliens) {
        if (currentAlienBullets >= maxBulletsAllowed) break;

        if (shooter->CanShoot()) {
            sf::FloatRect bounds = shooter->GetBounds();
            sf::Vector2f bulletPos;
            bulletPos.x = bounds.position.x + bounds.size.x / 2.0f - 5.0f;
            bulletPos.y = bounds.position.y + bounds.size.y;

            float bulletSpeed = 150.0f + (currentRound - 1) * 75.0f;
            sf::Vector2f bulletVel(0.0f, bulletSpeed);

            Bullet* newBullet = new Bullet(bulletTexture, bulletPos, bulletVel, false);
            bulletList.push_back(newBullet);

            shooter->ResetShootCooldown();
            currentAlienBullets++;
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