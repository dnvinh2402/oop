
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "AlienManager.hpp"
#include "CollisionManager.hpp"
#include "UI.hpp"
#include "BuffManager.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Sprite *backgroundSprite;

    GameState currentState;
    int highScore;
    ResourceManager resourceManager;
    CollisionManager collisionManager;
    // UI* ui;
    Player *player;
    AlienManager *alienManager;

    BuffManager *buffManager;

    std::vector<Bullet *> bullets;
    std::vector<Missile *> missiles;

    sf::Sprite *explosionSprite;
    sf::Sprite *shieldSprite;

    bool explosionActive;
    float explosionTimer;

    sf::RectangleShape restartButton;
    sf::Text *restartButtonText;

    // Các hàm nội bộ
    void DestroyNearestAliens(sf::Vector2f center);
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void CleanUpDeadEntities();
    void LoadHighScore();
    void SaveHighScore();

    void RestartGame();

public:
    Game();
    ~Game();
    void Run();
};