#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "AlienManager.hpp"
#include "BuffManager.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "CollisionManager.hpp"
#include "ResourceManager.hpp"
#include "GameState.hpp"
#include "UI.hpp"
#include "MainMenu.hpp" // Khai báo file MainMenu mới

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;
    ResourceManager resourceManager;

    Player* player;
    AlienManager* alienManager;
    BuffManager* buffManager;
    CollisionManager collisionManager;

    std::vector<Bullet*> bullets;
    std::vector<Missile*> missiles;

    sf::Sprite* backgroundSprite;
    sf::Sprite* shieldSprite;
    sf::Sprite* explosionSprite;

    bool explosionActive;
    float explosionTimer;

    GameState currentState;
    int highScore;

    UI* gameUI;
    MainMenu* mainMenu; // Khai báo đối tượng MainMenu để quản lý trang bìa

    void LoadHighScore();
    void SaveHighScore();
    void DestroyNearestAliens(sf::Vector2f center);
    void RestartGame();
    void UpdateView();

public:
    Game();
    ~Game();

    void ProcessEvents();
    void Update(float deltaTime);
    void CleanUpDeadEntities();
    void Render();
    void Run();
};