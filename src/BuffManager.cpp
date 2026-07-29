#include "BuffManager.hpp"

BuffManager::BuffManager()
{

}

BuffManager::~BuffManager()
{
    for (Buff* buff : buffs)
    {
        delete buff;
    }

    buffs.clear();
}

void BuffManager::SpawnBuff(sf::Texture* texture,
                            sf::Vector2f position,
                            BuffType type)
{
    Buff* newBuff = new Buff(texture, position, type);

    buffs.push_back(newBuff);
}

void BuffManager::Update(float deltaTime)
{
    for (Buff* buff : buffs)
    {
        if (buff->IsActive())
        {
            buff->Update(deltaTime);
        }
    }

    CleanUp();
}

void BuffManager::Render(sf::RenderWindow& window)
{
    for (Buff* buff : buffs)
    {
        if (buff->IsActive())
        {
            buff->Render(window);
        }
    }
}

void BuffManager::CleanUp()
{
    for (int i = buffs.size() - 1; i >= 0; i--)
    {
        if (!buffs[i]->IsActive())
        {
            delete buffs[i];
            buffs.erase(buffs.begin() + i);
        }
    }
}

std::vector<Buff*>& BuffManager::GetBuffs()
{
    return buffs;
}