#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
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
    std::unique_ptr<Player> player;
    std::unique_ptr<AlienManager> alienManager;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Missile>> missiles;
    std::unique_ptr<BuffManager> buffManager;
    CollisionManager collisionManager;
    std::unique_ptr<UI> gameUI;
    SoundManager soundManager;

    std::unique_ptr<sf::Sprite> backgroundSprite;
    std::unique_ptr<sf::Sprite> explosionSprite;
    bool explosionActive;
    float explosionTimer;
    std::unique_ptr<sf::Sprite> shieldSprite;

    GameState currentState;
    int highScore;

    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<GameOverMenu> gameOverMenu;
    std::unique_ptr<PauseMenu> pauseMenu;
    std::unique_ptr<ScoreHistoryMenu> scoreHistoryMenu; // Quản lý bảng lịch sử điểm
    
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

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Run();
    void ProcessEvents();
    void Update(float deltaTime);
    void CleanUpDeadEntities();
    void Render();
}; 