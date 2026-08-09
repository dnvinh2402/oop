#pragma once
#include <vector>
#include "Player.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"
#include "BuffManager.hpp"
#include "ResourceManager.hpp"
#include "Buff.hpp"
#include "SoundManager.hpp"

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    // Thuật toán AABB quét va chạm giữa các mảng
void CheckCollisions(
    Player* player,
    const std::vector<Alien*>& aliens,
    const std::vector<Bullet*>& bullets,
    const std::vector<Buff*>& buffs,
    BuffManager* buffManager,
    ResourceManager& resourceManager,
    SoundManager &soundManager);
void AwardScore(Player* player, Alien* alien);
};