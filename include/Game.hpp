#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "AlienManager.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "BuffManager.hpp"
#include "CollisionManager.hpp"
#include "UI.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "GameOverMenu.hpp"
#include "PauseMenu.hpp"
#include "ScoreHistoryMenu.hpp" // Thêm header lịch sử điểm
#include "SoundManager.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::View gameView;
    ResourceManager resourceManager;
    Player *player;
    AlienManager *alienManager;
    std::vector<Bullet *> bullets;
    std::vector<Missile *> missiles;
    BuffManager *buffManager;
    CollisionManager collisionManager;
    UI *gameUI;
    SoundManager soundManager;

    sf::Sprite *backgroundSprite;
    sf::Sprite *explosionSprite;
    bool explosionActive;
    float explosionTimer;
    sf::Sprite *shieldSprite;

    GameState currentState;
    int highScore;

    MainMenu *mainMenu;
    GameOverMenu *gameOverMenu;
    PauseMenu *pauseMenu;
    ScoreHistoryMenu *scoreHistoryMenu; // Quản lý bảng lịch sử điểm
    
    bool isPaused;
    bool viewingHistory;                 // Trạng thái đang xem màn hình lịch sử điểm
    std::vector<int> matchHistory;       // Lưu tối đa 5 điểm trận đấu gần nhất


    void LoadHighScore();
    void SaveHighScore();
    void LoadHistory();
    void SaveHistory();
    void AddScoreToHistory(int score);
    void DestroyNearestAliens(sf::Vector2f center);
    void RestartGame();
    void UpdateView();

    sf::Texture* GetAlienTextureForRound(int round);
    
public:
    Game();
    ~Game();

    void Run();
    void ProcessEvents();
    void Update(float deltaTime);
    void CleanUpDeadEntities();
    void Render();
}; 