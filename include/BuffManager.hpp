#pragma once

#include <vector>
#include <memory>
#include "Buff.hpp"

class BuffManager
{
private:
    std::vector<std::unique_ptr<Buff>> buffs;

public:
    BuffManager();
    ~BuffManager();

    BuffManager(const BuffManager&) = delete;
    BuffManager& operator=(const BuffManager&) = delete;

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

    // Trả về danh sách con trỏ thô (non-owning)
    std::vector<Buff*> GetBuffs() const;

    // Xóa toàn bộ Buff (sử dụng khi restart game)
    void ClearAll();
};