// #pragma once
// #include <SFML/Graphics.hpp>
// #include <vector>
// #include "GameState.hpp"
// #include "ResourceManager.hpp"
// #include "Player.hpp"
// #include "Bullet.hpp"
// #include "AlienManager.hpp"
// #include "CollisionManager.hpp"
// #include "UI.hpp"

// class Game {
// private:
//     sf::RenderWindow window;
//     GameState currentState;
    
//     // Các Class Quản lý
//     ResourceManager resourceManager;
//     CollisionManager collisionManager;
//     UI* ui; // Con trỏ UI

//     // Các Thực thể trong game
//     Player* player;
//     AlienManager* alienManager;
//     std::vector<Bullet*> bullets;

//     // Các hàm nội bộ
//     void ProcessEvents();
//     void Update(float deltaTime);
//     void Render();
//     void CleanUpDeadEntities(); // Cực kỳ quan trọng để dọn rác (delete) các viên đạn/quái đã chết

// public:
//     Game();
//     ~Game();
//     void Run();
// };


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Tạm thời khóa các thư viện chưa có file .cpp
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "AlienManager.hpp"
#include "CollisionManager.hpp"
#include "UI.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Sprite* backgroundSprite;
    
    // Tạm thời khóa các Class Quản lý và Thực thể
    // GameState currentState;
    ResourceManager resourceManager;
    CollisionManager collisionManager;
    // UI* ui;
    Player* player;
    AlienManager* alienManager;
    std::vector<Bullet*> bullets;

    // Các hàm nội bộ
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void CleanUpDeadEntities(); 

public:
    Game();
    ~Game();
    void Run();
};