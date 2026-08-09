#include "BuffManager.hpp"

BuffManager::BuffManager()
{

}

BuffManager::~BuffManager() = default;

void BuffManager::SpawnBuff(sf::Texture* texture,
                            sf::Vector2f position,
                            BuffType type)
{
    buffs.push_back(std::make_unique<Buff>(texture, position, type));
}

void BuffManager::Update(float deltaTime)
{
    for (auto &buffPtr : buffs)
    {
        Buff* buff = buffPtr.get();
        if (buff->IsActive())
        {
            buff->Update(deltaTime);
        }
    }

    CleanUp();
}

void BuffManager::Render(sf::RenderWindow& window)
{
    for (auto &buffPtr : buffs)
    {
        Buff* buff = buffPtr.get();
        if (buff->IsActive())
        {
            buff->Render(window);
        }
    }
}

void BuffManager::CleanUp()
{
    for (int i = (int)buffs.size() - 1; i >= 0; i--)
    {
        if (!buffs[i]->IsActive())
        {
            buffs.erase(buffs.begin() + i);
        }
    }
}

std::vector<Buff*> BuffManager::GetBuffs() const
{
    std::vector<Buff*> res;
    res.reserve(buffs.size());
    for (const auto &p : buffs) res.push_back(p.get());
    return res;
}

void BuffManager::ClearAll()
{
    buffs.clear();
}
