#pragma once
#include <vector>
#include <memory>
#include "Alien.hpp"
#include "Bullet.hpp"

class AlienManager {
private:
    std::vector<std::unique_ptr<Alien>> aliens;
    float moveSpeed;
    bool movingRight;

    int currentRound;
    int maxRounds;

public:
    AlienManager();
    ~AlienManager();

    AlienManager(const AlienManager&) = delete;
    AlienManager& operator=(const AlienManager&) = delete;

    void InitializeSwarm(sf::Texture* alienTexture);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);
    
    void AlienShoot(std::vector<std::unique_ptr<Bullet>>& bulletList, sf::Texture* bulletTexture);
    
    // Trả về danh sách con trỏ thô không sở hữu để sử dụng bên ngoài
    std::vector<Alien*> GetAliens() const;

    void StartNextRound(sf::Texture* alienTexture);
    bool IsRoundCleared();       
    bool IsFinalRound();        
    int GetCurrentRound() { return currentRound; }

    void Reset(sf:: Texture* alienTexture);
};