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

                    if (alien->GetMaxHealth() > 1)
                    {
                        int hitScore = alien->CalculateBossHitScore();
                        player->AddScore(hitScore);

                        if (!alien->IsActive())
                        {
                            soundManager.Play("enemyDead");
                            int killScore = alien->CalculateBossKillScore();
                            AwardScore(player, alien);
                        }
                    }
                    else
                    {
                        if (!alien->IsActive())
                        {
                            soundManager.Play("enemyDead");
                            AwardScore(player, alien);
                        }
                    }

                    if (!alien->IsActive())
                    {
                        if (rand() % 100 < 30)
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
                    if (player->IsInvincible())
                    {
                        bullet->Destroy();
                        continue;
                    }

                    bool shielded = player->HasShield();
                    player->TakeDamage();
                    soundManager.Play(shielded ? "shield" : "hit");
                    if (!shielded)
                    {
                        std::cout << "CANH BAO! Phi thuyen trung dan!\n";
                    }

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