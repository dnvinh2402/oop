#pragma once

#include <vector>
#include "Buff.hpp"

class BuffManager
{
private:
    std::vector<Buff*> buffs;

public:
    BuffManager();
    ~BuffManager();

    // Sinh một Buff tại vị trí Alien bị tiêu diệt
    void SpawnBuff(sf::Texture* texture,
                   sf::Vector2f position,
                   BuffType type);

    // Cập nhật toàn bộ Buff
    void Update(float deltaTime);

    // Vẽ toàn bộ Buff
    void Render(sf::RenderWindow& window);

    // Xóa Buff đã hết hiệu lực
    void CleanUp();

    // Trả về danh sách Buff
    std::vector<Buff*>& GetBuffs();
};