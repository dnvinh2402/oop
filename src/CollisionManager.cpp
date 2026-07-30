#include "CollisionManager.hpp"
#include <iostream>
#include <cstdlib>

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckCollisions(
    Player *player,
    std::vector<Alien *> &aliens,
    std::vector<Bullet *> &bullets,
    std::vector<Buff *> &buffs,
    BuffManager *buffManager,
    ResourceManager &resourceManager)
{
    for (Bullet *bullet : bullets)
    {
        if (!bullet->IsActive())
            continue;

        sf::FloatRect bulletBounds = bullet->GetBounds();

        // =========================
        // Đạn của Player
        // =========================
        if (bullet->IsPlayerBullet())
        {
            for (Alien *alien : aliens)
            {
                if (!alien->IsActive())
                    continue;

                if (bulletBounds.findIntersection(alien->GetBounds()).has_value())
                {
                    alien->TakeDamage(1);
                    bullet->Destroy();

                    // 15% tỉ lệ rơi Buff
                    // 50 de test
                    if (rand() % 100 < 50)
                    {
                        BuffType type;

                        int randomType = rand() % 3;

                        if (randomType == 0)
                            type = BuffType::doubleShot;
                        else if (randomType == 1)
                            type = BuffType::Shield;
                        else
                            type = BuffType::Bomb;

                        sf::FloatRect bounds = alien->GetBounds();

                        sf::Vector2f pos;
                        pos.x = bounds.position.x + bounds.size.x / 2.f - 12.f;
                        pos.y = bounds.position.y + bounds.size.y / 2.f - 12.f;

                        sf::Texture *texture = nullptr;

                        switch (type)
                        {
                        case BuffType::doubleShot:
                            texture = resourceManager.GetTexture("doubleShot");
                            break;

                        case BuffType::Shield:
                            texture = resourceManager.GetTexture("shield");
                            break;

                        case BuffType::Bomb:
                            texture = resourceManager.GetTexture("bomb");
                            break;
                        }

                        buffManager->SpawnBuff(texture, pos, type);
                    }
                    player->AddScore(alien->GetPoints());
                    std::cout << "BUM! Tieu diet quai vat (+ "
                              << alien->GetPoints()
                              << " diem)\n";

                    break;
                }
            }
        }
        // =========================
        // Đạn của Alien
        // =========================
        else
        {
            if (player->IsActive())
            {
                if (bulletBounds.findIntersection(player->GetBounds()).has_value())
                {
                    player->TakeDamage();
                    bullet->Destroy();

                    std::cout << "CANH BAO! Phi thuyen trung dan!\n";
                }
            }
        }
    }
    // =========================
    // Player nhặt Buff
    // =========================
    for (Buff *buff : buffs)
    {
        if (!buff->IsActive())
            continue;

        if (player->GetBounds().findIntersection(buff->GetBounds()).has_value())
        {
            switch (buff->GetType())
            {
            case BuffType::doubleShot:
                player->ActivateDoubleShot();
                break;

            case BuffType::Shield:
                player->ActivateShield();
                break;

            case BuffType::Bomb:
                player->ActivateBomb();
                break;
            }
            buff->Destroy();
        }
    }
}