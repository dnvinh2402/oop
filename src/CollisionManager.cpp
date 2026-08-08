#include "CollisionManager.hpp"
#include <iostream>
#include <cstdlib>

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
void CollisionManager::AwardScore(Player* player, Alien* alien)
{
    if (alien->GetMaxHealth() > 1)
    {
        int killScore = alien->CalculateBossKillScore();
        player->AddScore(killScore);

        std::cout << "HA GUC BOSS ! (+ "
                  << killScore << " diem)\n";
    }
    else
    {
        int normalScore = alien->CalculateNormalScore();
        player->AddScore(normalScore);

        // std::cout << "TIEU DIET LINH THUONG! (+ "
        //           << normalScore << " diem)\n";
    }
}
void CollisionManager::CheckCollisions(
    Player *player,
    std::vector<Alien *> &aliens,
    std::vector<Bullet *> &bullets,
    std::vector<Buff *> &buffs,
    BuffManager *buffManager,
    ResourceManager &resourceManager,
    SoundManager &soundManager)
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

                    // PHÂN LOẠI TÍNH ĐIỂM: BOSS VS LÍNH THƯỜNG
                    if (alien->GetMaxHealth() > 1)
                    {
                        // 1. XỬ LÝ CHO BOSS: Mỗi lần bắn trúng được cộng điểm (200đ -> thấp nhất 30đ)
                        int hitScore = alien->CalculateBossHitScore();
                        player->AddScore(hitScore);
                        // std::cout << "BAN TRUNG BOSS! (+ " << hitScore << " diem)\n";

                        // Nếu Boss chết hẳn -> Cộng thêm 1000 điểm thưởng tiêu diệt
                        if (!alien->IsActive())
                        {
                            soundManager.Play("enemyDead");
                            int killScore = alien->CalculateBossKillScore();
                            AwardScore(player, alien);
                        }
                    }
                    else
                    {
                        // 2. XỬ LÝ CHO LÍNH THƯỜNG: Chỉ cộng điểm khi tiêu diệt hoàn toàn
                        if (!alien->IsActive())
                        {
                            soundManager.Play("enemyDead");
                            AwardScore(player, alien);
                        }
                    }

                    // Xử lý tỉ lệ rơi Buff (50% cho test) khi quái/Boss bất kỳ bị tiêu diệt
                    if (!alien->IsActive())
                    {
                        if (rand() % 100 < 50)
                        {
                            BuffType type;
                            int randomType = rand() % 3; // 3 loại: doubleShot, Shield, Bomb

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
                    }

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
                    soundManager.Play("hit");
                    std::cout << "CANH BAO! Phi thuyen trung dan!\n";

                    bullet->Destroy();
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
                soundManager.Play("pickup");
                break;

            case BuffType::Shield:
                player->ActivateShield(); // Nhặt item khiên để bật khiên bảo vệ
                soundManager.Play("pickup");
                break;

            case BuffType::Bomb:
                player->ActivateBomb();
                soundManager.Play("pickup");
                break;
            }
            buff->Destroy();
        }
    }
}