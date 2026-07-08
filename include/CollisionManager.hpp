#pragma once
#include <vector>
#include "Player.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    // Thuật toán AABB quét va chạm giữa các mảng
    void CheckCollisions(Player* player, std::vector<Alien*>& aliens, std::vector<Bullet*>& bullets);
};