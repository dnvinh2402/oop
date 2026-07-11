#include "CollisionManager.hpp"
#include <iostream>

CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::CheckCollisions(Player* player, std::vector<Alien*>& aliens, std::vector<Bullet*>& bullets) {
    // Duyệt qua toàn bộ đạn đang bay trên màn hình
    for (Bullet* bullet : bullets) {
        if (!bullet->IsActive()) continue;

        sf::FloatRect bulletBounds = bullet->GetBounds();

        // TRƯỜNG HỢP 1: Đạn của người chơi bắn lên
        if (bullet->IsPlayerBullet()) {
            for (Alien* alien : aliens) {
                if (!alien->IsActive()) continue;

                // Trong SFML 3, findIntersection trả về std::optional
                if (bulletBounds.findIntersection(alien->GetBounds()).has_value()) {
                    // Trúng đích!
                    alien->Destroy();  // Kích hoạt hàm hủy của quái (ẩn đi)
                    bullet->Destroy(); // Phá hủy viên đạn

                    // Tạm in ra console để theo dõi (sau này sẽ làm UI cộng điểm)
                    std::cout << "BUM! Tieu diet quai vat (+ " << alien->GetPoints() << " diem)\n";
                    break; // Viên đạn này đã nổ, chuyển sang xét viên đạn khác
                }
            }
        } 
        // TRƯỜNG HỢP 2: Đạn của quái vật rơi xuống
        else {
            if (player->IsActive()) {
                if (bulletBounds.findIntersection(player->GetBounds()).has_value()) {
                    player->TakeDamage(); // Trừ mạng phi thuyền
                    bullet->Destroy();    // Phá hủy quả cầu vàng
                    std::cout << "CANH BAO! Phi thuyen trung dan!\n";
                }
            }
        }
    }
}