#include "Game.hpp"
#include "MainMenu.hpp"
#include "GameOverMenu.hpp"
#include "ScoreHistoryMenu.hpp" // Thêm header ScoreHistoryMenu
#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include "GlobalAudio.hpp"

const float WORLD_WIDTH = 900.0f;
const float WORLD_HEIGHT = 900.0f;

Game::Game() : window(sf::VideoMode({900, 900}), "My first game", sf::Style::Default | sf::Style::Resize), isPaused(false)
{
    gameView.setSize(sf::Vector2f(WORLD_WIDTH, WORLD_HEIGHT));
    gameView.setCenter(sf::Vector2f(WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f));
    window.setView(gameView);
    resourceManager.LoadTexture("player", "assets/images/player.png");
    std::cout << "Da load xong player texture\n";

    resourceManager.LoadTexture("enemy", "assets/images/enemy.png");

    alienManager = new AlienManager();
    alienManager->InitializeSwarm(resourceManager.GetTexture("enemy"));
    buffManager = new BuffManager();

    resourceManager.LoadTexture("bullet", "assets/images/bullet.png");
    std::cout << "Da load xong bullet texture\n";
    resourceManager.LoadTexture("alien_bullet", "assets/images/alien_bullet.png");
    std::cout << "Da load xong alien bullet texture\n";
    resourceManager.LoadTexture("doubleShot", "assets/images/doubleShot.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("missile", "assets/images/missile.png");
    std::cout << "Da load xong missile\n";

    resourceManager.LoadTexture("shield", "assets/images/shield.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("shield_effect", "assets/images/shield_effect.png");
    std::cout << "Da load xong buff player\n";

    resourceManager.LoadTexture("bomb", "assets/images/bomb.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("explosion", "assets/images/explosion.png");

    explosionSprite = new sf::Sprite(
        *resourceManager.GetTexture("explosion"));

    explosionActive = false;
    explosionTimer = 0.f;

    resourceManager.LoadTexture("background", "assets/images/background.png");
    std::cout << "Da load xong background texture\n";
    resourceManager.LoadFont("arial", "assets/font/arial.ttf");
    std::cout << "Da load xong font\n";

    soundManager.LoadSound("shoot", "assets/audio/shoot.wav");
    std::cout << "Da load xong am thanh dan\n";
    soundManager.LoadSound("pickup", "assets/audio/pickup.wav");
    std::cout << "Da load xong am thanh nhat\n";
    soundManager.LoadSound("explosion", "assets/audio/explosion.wav");
    std::cout << "Da load xong am thanh vu no\n";
    soundManager.LoadSound("hit", "assets/audio/hit.wav");
    std::cout << "Da load xong am thanh bị trung dan\n";
    soundManager.LoadSound("enemyDead", "assets/audio/enemy_eliminated.wav");
    std::cout << "Da load xong am thanh tieu diet quai\n";
    soundManager.LoadSound("shield", "assets/audio/shield.wav");
    std::cout << "Da load xong am thanh dan bi chan\n";

    soundManager.LoadMusic("assets/audio/background.ogg");
    soundManager.PlayMusic();

    sf::Vector2f startPos(WORLD_WIDTH / 2.0f, WORLD_HEIGHT - 100.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);
    std::cout << "Da tao xong Player\n";

    currentState = GameState::MainMenu;
    LoadHighScore();
    LoadHistory(); // Load lịch sử trận đấu

    gameUI = new UI(resourceManager.GetFont("arial"));

    mainMenu = new MainMenu(resourceManager.GetFont("arial"), resourceManager.GetTexture("background"), highScore);
    gameOverMenu = nullptr;
    pauseMenu = new PauseMenu(resourceManager.GetFont("arial"));
    pauseMenu->SetVolume(
        GlobalAudio::volume,
        GlobalAudio::isMuted);
    scoreHistoryMenu = nullptr;
    viewingHistory = false;

    backgroundSprite = new sf::Sprite(*resourceManager.GetTexture("background"));

    shieldSprite = new sf::Sprite(*resourceManager.GetTexture("shield_effect"));
    sf::Vector2u size = resourceManager.GetTexture("shield_effect")->getSize();

    shieldSprite->setScale(sf::Vector2f(64.f / size.x, 64.f / size.y));

    sf::Vector2u textureSize = resourceManager.GetTexture("background")->getSize();
    float scaleX = WORLD_WIDTH / textureSize.x;
    float scaleY = WORLD_HEIGHT / textureSize.y;
    backgroundSprite->setScale(sf::Vector2f(scaleX, scaleY));
    std::cout << "Da tao xong Background\n";
}

Game::~Game()
{
    delete player;
    delete backgroundSprite;
    delete alienManager;
    delete buffManager;
    delete explosionSprite;
    delete shieldSprite;
    delete gameUI;
    delete mainMenu;
    delete gameOverMenu;
    delete pauseMenu;
    delete scoreHistoryMenu;

    for (Bullet *bullet : bullets)
    {
        delete bullet;
    }
    for (Missile *missile : missiles)
    {
        delete missile;
    }
    missiles.clear();
    bullets.clear();
}
void Game::ProcessEvents()
{
    std::optional<sf::Event> event;

    while (event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        // Bắt sự kiện di chuyển chuột
        if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f mousePos(mouseMoved->position.x, mouseMoved->position.y);
            if (currentState == GameState::MainMenu)
            {
                if (viewingHistory && scoreHistoryMenu)
                {
                    scoreHistoryMenu->Update(mousePos);
                }
                else
                {
                    mainMenu->Update(mousePos);
                }
            }
            else if ((currentState == GameState::GameOver || currentState == GameState::Victory) && gameOverMenu)
            {
                gameOverMenu->Update(mousePos);
            }
            else if (currentState == GameState::Playing && isPaused)
            {
                pauseMenu->Update(mousePos);
            }
        }

        // Bắt sự kiện từ bàn phím
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (currentState == GameState::Playing && !isPaused)
            {
                if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    player->Shoot(bullets, resourceManager.GetTexture("bullet"));
                    soundManager.Play("shoot");
                }
            }
            else if (currentState == GameState::MainMenu && !viewingHistory)
            {
                if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    RestartGame();
                    currentState = GameState::Playing;
                }
            }
            else if (currentState == GameState::GameOver || currentState == GameState::Victory)
            {
                if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    RestartGame();
                }
            }
        }

        // Bắt sự kiện từ chuột
        if (const auto *mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseClicked->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePos(mouseClicked->position.x, mouseClicked->position.y);

                if (currentState == GameState::Playing)
                {
                    if (pauseMenu->IsPauseButtonClicked(mousePos))
                    {
                        isPaused = !isPaused;
                        if (isPaused)
                        {
                            pauseMenu->SetVolume(GlobalAudio::volume, GlobalAudio::isMuted);
                        }
                    }
                    else if (isPaused)
                    {
                        int action = pauseMenu->HandleClick(mousePos);
                        if (action == 1)
                        {
                            isPaused = false;
                        }
                        else if (action == 2)
                        {
                            isPaused = false;
                            mainMenu->SetVolume((int)GlobalAudio::volume, GlobalAudio::isMuted);
                            RestartGame();
                            currentState = GameState::MainMenu;
                        }
                        if (action >= 3)
                        {
                            soundManager.UpdateVolume();
                        }
                    }
                    else if (!isPaused)
                    {
                        player->Shoot(bullets, resourceManager.GetTexture("bullet"));
                        soundManager.Play("shoot");
                    }
                }
                else if (currentState == GameState::MainMenu)
                {
                    if (viewingHistory)
                    {
                        if (scoreHistoryMenu && scoreHistoryMenu->IsBackButtonClicked(mousePos))
                        {
                            delete scoreHistoryMenu;
                            scoreHistoryMenu = nullptr;
                            viewingHistory = false; // Đóng bảng lịch sử để về Main Menu chính
                        }
                    }
                    else
                    {
                        int action = mainMenu->HandleClick(mousePos);
                        if (action == 1)
                        {
                            RestartGame();
                            currentState = GameState::Playing;
                        }
                        else if (action == 2)
                        { // Bấm nút xem lịch sử điểm
                            viewingHistory = true;
                            delete scoreHistoryMenu;
                            scoreHistoryMenu = new ScoreHistoryMenu(resourceManager.GetFont("arial"), matchHistory);
                        }
                        else if (action == 3)
                        {
                            soundManager.UpdateVolume();
                            std::cout << "--> Trang thai Mute: " << (mainMenu->IsMuted() ? "ON" : "OFF") << "\n";
                        }
                        else if (action == 4 || action == 5)
                        {
                            soundManager.UpdateVolume();
                            std::cout << "--> Am luong hien tai: " << mainMenu->GetVolume() << "%\n";
                        }
                    }
                }
                else if (currentState == GameState::GameOver || currentState == GameState::Victory)
                {
                    if (gameOverMenu)
                    {
                        int choice = gameOverMenu->HandleClick(mousePos);
                        if (choice == 1)
                        {
                            RestartGame();
                        }
                        else if (choice == 2)
                        {
                            RestartGame();
                            currentState = GameState::MainMenu;
                        }
                    }
                }
            }
        }
    }
}
void Game::Update(float deltaTime)
{
    soundManager.UpdateVolume();
    if (isPaused)
        return;

    if (currentState == GameState::Playing)
    {
        player->Update(deltaTime);
        if (player->IsBombReady())
        {
            sf::FloatRect playerBounds = player->GetBounds();
            sf::Vector2u missileSize = resourceManager.GetTexture("missile")->getSize();
            sf::Vector2f pos;
            pos.x = playerBounds.position.x + playerBounds.size.x / 2.f - missileSize.x / 2.f;
            pos.y = playerBounds.position.y - missileSize.y;

            missiles.push_back(new Missile(resourceManager.GetTexture("missile"), pos));
            player->ResetBomb();
        }
        alienManager->Update(deltaTime);
        buffManager->Update(deltaTime);

        for (Bullet *bullet : bullets)
            bullet->Update(deltaTime);
        for (Missile *missile : missiles)
            missile->Update(deltaTime);

        for (Missile *missile : missiles)
        {
            if (!missile->IsActive())
                continue;
            for (Alien *alien : alienManager->GetAliens())
            {
                if (!alien->IsActive())
                    continue;
                if (missile->GetBounds().findIntersection(alien->GetBounds()).has_value())
                {
                    missile->Destroy();
                    soundManager.Play("explosion");
                    DestroyNearestAliens(missile->GetPosition());
                    explosionSprite->setPosition(missile->GetPosition());
                    explosionActive = true;
                    explosionTimer = 0.3f;
                    break;
                }
            }
        }
        if (explosionActive)
        {
            explosionTimer -= deltaTime;
            if (explosionTimer <= 0.f)
                explosionActive = false;
        }

        alienManager->AlienShoot(bullets, resourceManager.GetTexture("alien_bullet"));

        collisionManager.CheckCollisions(
            player, alienManager->GetAliens(), bullets,
            buffManager->GetBuffs(), buffManager, resourceManager, soundManager);

        CleanUpDeadEntities();

        if (!player->IsActive())
        {
            currentState = GameState::GameOver;
            AddScoreToHistory(player->GetScore()); // Lưu lịch sử trận thua

            delete gameOverMenu;
            gameOverMenu = new GameOverMenu(resourceManager.GetFont("arial"), player->GetScore(), false);

            if (player->GetScore() > highScore)
            {
                highScore = player->GetScore();
                SaveHighScore();
            }
        }
        else if (alienManager->IsRoundCleared())
        {
            if (alienManager->IsFinalRound())
            {
                currentState = GameState::Victory;
                AddScoreToHistory(player->GetScore()); // Lưu lịch sử trận thắng

                delete gameOverMenu;
                gameOverMenu = new GameOverMenu(resourceManager.GetFont("arial"), player->GetScore(), true);

                if (player->GetScore() > highScore)
                {
                    highScore = player->GetScore();
                    SaveHighScore();
                }
            }
            else
            {
                alienManager->StartNextRound(resourceManager.GetTexture("enemy"));
            }
        }
    }

    gameUI->Update(player, currentState, highScore);
}

void Game::CleanUpDeadEntities()
{
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        if (!bullets[i]->IsActive())
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    for (int i = missiles.size() - 1; i >= 0; i--)
    {
        if (!missiles[i]->IsActive())
        {
            delete missiles[i];
            missiles.erase(missiles.begin() + i);
        }
    }
}

void Game::Render()
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);
    window.setView(gameView);

    if (currentState == GameState::MainMenu)
    {
        mainMenu->Render(window);
        if (viewingHistory && scoreHistoryMenu)
        {
            scoreHistoryMenu->Render(window); // Vẽ trang lịch sử điểm đè lên Main Menu
        }
    }
    else if (currentState == GameState::GameOver || currentState == GameState::Victory)
    {
        window.draw(*backgroundSprite);
        player->Render(window);
        alienManager->Render(window);
        if (gameOverMenu)
            gameOverMenu->Render(window);
    }
    else
    {
        window.draw(*backgroundSprite);

        if (player->HasShield())
        {
            sf::FloatRect bounds = player->GetBounds();
            shieldSprite->setPosition(sf::Vector2f(
                bounds.position.x + bounds.size.x / 2.f - shieldSprite->getGlobalBounds().size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f - shieldSprite->getGlobalBounds().size.y / 2.f));
            window.draw(*shieldSprite);
        }

        player->Render(window);
        alienManager->Render(window);
        buffManager->Render(window);

        for (Missile *missile : missiles)
            missile->Render(window);
        for (Bullet *bullet : bullets)
            bullet->Render(window);

        if (explosionActive)
            window.draw(*explosionSprite);

        gameUI->Render(window);
        pauseMenu->Render(window, isPaused);
    }

    window.display();
}

void Game::Run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Game::LoadHighScore()
{
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    else
    {
        highScore = 0;
    }
}

void Game::SaveHighScore()
{
    std::ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

void Game::LoadHistory()
{
    matchHistory.clear();
    std::ifstream file("history.txt");
    if (file.is_open())
    {
        int score;
        while (file >> score)
        {
            matchHistory.push_back(score);
        }
        file.close();
    }
}

void Game::SaveHistory()
{
    std::ofstream file("history.txt");
    if (file.is_open())
    {
        for (int score : matchHistory)
        {
            file << score << "\n";
        }
        file.close();
    }
}

void Game::AddScoreToHistory(int score)
{
    matchHistory.insert(matchHistory.begin(), score); // Đưa trận mới nhất lên đầu danh sách
    if (matchHistory.size() > 5)
    {
        matchHistory.pop_back(); // Giới hạn đúng 5 trận gần nhất
    }
    SaveHistory();
}

void Game::DestroyNearestAliens(sf::Vector2f center)
{
    struct Target
    {
        Alien *alien;
        float distance;
    };
    std::vector<Target> targets;

    for (Alien *alien : alienManager->GetAliens())
    {
        if (!alien->IsActive())
            continue;
        sf::FloatRect rect = alien->GetBounds();
        float x = rect.position.x + rect.size.x / 2.f;
        float y = rect.position.y + rect.size.y / 2.f;
        float dx = x - center.x;
        float dy = y - center.y;

        Target t;
        t.alien = alien;
        t.distance = dx * dx + dy * dy;
        targets.push_back(t);
    }

    std::sort(targets.begin(), targets.end(), [](const Target &a, const Target &b)
              { return a.distance < b.distance; });

    int count = std::min(5, (int)targets.size());
    for (int i = 0; i < count; i++)
    {
        targets[i].alien->Destroy();
    }
}

void Game::RestartGame()
{
    isPaused = false;
    delete player;
    sf::Vector2f startPos(WORLD_WIDTH / 2.0f, WORLD_HEIGHT - 100.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);

    for (Bullet *bullet : bullets)
        delete bullet;
    bullets.clear();

    for (Missile *missile : missiles)
        delete missile;
    missiles.clear();

    for (Buff *buff : buffManager->GetBuffs())
        delete buff;
    buffManager->GetBuffs().clear();

    alienManager->Reset(resourceManager.GetTexture("enemy"));
    currentState = GameState::Playing;
}

void Game::UpdateView()
{
    float windowRatio = (float)window.getSize().x / (float)window.getSize().y;
    float worldRatio = WORLD_WIDTH / WORLD_HEIGHT;

    float sizeX = 1.0f, sizeY = 1.0f;
    float posX = 0.0f, posY = 0.0f;

    if (windowRatio > worldRatio)
    {
        sizeX = worldRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    }
    else
    {
        sizeY = windowRatio / worldRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    gameView.setViewport(sf::FloatRect(sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY)));
    window.setView(gameView);
}