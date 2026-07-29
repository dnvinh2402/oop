#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional> // Bắt buộc phải có cho SFML 3 Event

// Khởi tạo cửa sổ y hệt code cũ của bạn
Game::Game() : window(sf::VideoMode({800, 600}), "My first game")
{

    resourceManager.LoadTexture("player", "assets/images/player.png");
    std::cout << "Da load xong player texture\n";

    resourceManager.LoadTexture("enemy", "assets/images/enemy.png");

    // Khởi tạo nhạc trưởng và sinh ra bầy quái
    alienManager = new AlienManager();
    alienManager->InitializeSwarm(resourceManager.GetTexture("enemy"));
    buffManager = new BuffManager();

    resourceManager.LoadTexture("bullet", "assets/images/bullet.png");
    std::cout << "Da load xong bullet texture\n";
    resourceManager.LoadTexture("alien_bullet", "assets/images/alien_bullet.png");
    std::cout << "Da load xong alien bullet texture\n";
    resourceManager.LoadTexture("rapid_fire", "assets/images/rapid_fire.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("missile", "assets/images/missile.png");
    std::cout << "Da load xong missile\n";

    resourceManager.LoadTexture("shield", "assets/images/shield.png");
    std::cout << "Da load xong buff bullet\n";

    // resourceManager.LoadTexture("explosion", "assets/images/explosion.png");
    // std::cout << "Da load xong buff bullet\n";
    resourceManager.LoadTexture("bomb", "assets/images/bomb.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("background", "assets/images/background.png");
    std::cout << "Da load xong background texture\n";
    resourceManager.LoadFont("arial", "assets/font/arial.ttf");
    std::cout << "Da load xong font\n";

    sf::Vector2f startPos(400.0f, 550.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);
    std::cout << "Da tao xong Player\n";

    currentState = GameState::Playing;
    LoadHighScore();

    backgroundSprite = new sf::Sprite(*resourceManager.GetTexture("background"));

    // Co giãn ảnh nền cho vừa khít cửa sổ 800x600
    sf::Vector2u textureSize = resourceManager.GetTexture("background")->getSize();
    float scaleX = 800.0f / textureSize.x;
    float scaleY = 600.0f / textureSize.y;
    backgroundSprite->setScale(sf::Vector2f(scaleX, scaleY));
    std::cout << "Da tao xong Background\n";
    // explosionSprite.setTexture(
    // *resourceManager.GetTexture("explosion"));

    // explosionActive = false;
    // explosionTimer = 0.f;
}

Game::~Game()
{
    delete player;
    delete backgroundSprite;
    delete alienManager;
    delete buffManager;

    for (Bullet *bullet : bullets)
    {
        delete bullet;
    }
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
                // Missile trúng Alien
                missile->Destroy();

                DestroyNearestAliens(missile->GetPosition());

                break;
            }
        }
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

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Space)
            {
                player->Shoot(bullets, resourceManager.GetTexture("bullet"));
            }
        }
    }
}

void Game::Update(float deltaTime)
{
    if (currentState == GameState::Playing)
    {
        player->Update(deltaTime);
        if (player->IsBombReady())
        {
            sf::Vector2f pos = player->GetPosition();

            pos.x += 16.f;
            pos.y -= 10.f;

            missiles.push_back(
                new Missile(
                    resourceManager.GetTexture("missile"),
                    pos));

            player->ResetBomb();
        }
        alienManager->Update(deltaTime);
        buffManager->Update(deltaTime);

        for (Bullet *bullet : bullets)
        {
            bullet->Update(deltaTime);
        }
        for (Missile *missile : missiles)
        {
            missile->Update(deltaTime);
        }

        alienManager->AlienShoot(bullets, resourceManager.GetTexture("alien_bullet"));
        collisionManager.CheckCollisions(
            player,
            alienManager->GetAliens(),
            bullets,
            buffManager->GetBuffs(),
            buffManager,
            resourceManager);

        CleanUpDeadEntities();

        // Kiểm tra Player còn sống không
        if (!player->IsActive())
        {
            currentState = GameState::GameOver;
            if (player->GetScore() > highScore)
            {
                highScore = player->GetScore();
                SaveHighScore();
                std::cout << "KY LUC MOI! Diem: " << highScore << "\n";
            }
            else
            {
                std::cout << "Game Over. Diem: " << player->GetScore() << " | Ky luc: " << highScore << "\n";
            }
        }
        // Kiểm tra đợt quái hiện tại đã bị tiêu diệt hết chưa
        else if (alienManager->IsRoundCleared())
        {
            if (alienManager->IsFinalRound())
            {
                // Đã dẹp sạch đợt cuối cùng -> Thắng game
                currentState = GameState::Victory;
                if (player->GetScore() > highScore)
                {
                    highScore = player->GetScore();
                    SaveHighScore();
                }
                std::cout << "CHIEN THANG! Diem cuoi cung: " << player->GetScore() << "\n";
            }
            else
            {
                // Còn round tiếp theo -> chuyển sang đợt mới mạnh hơn
                alienManager->StartNextRound(resourceManager.GetTexture("enemy"));
                std::cout << "Chuyen sang Round " << alienManager->GetCurrentRound() << "!\n";
            }
        }
    }
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
}

void Game::Render()
{
    // Bôi màu nền xám giống hệt file main cũ của bạn
    window.clear(sf::Color(127, 127, 127));

    window.draw(*backgroundSprite);
    player->Render(window);
    alienManager->Render(window);
    buffManager->Render(window);

    for (Missile *missile : missiles)
    {
        missile->Render(window);
    }

    for (Bullet *bullet : bullets)
    {
        bullet->Render(window);
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
        t.distance = dx * dx + dy * dy; // không cần sqrt

        targets.push_back(t);
    }

    std::sort(targets.begin(), targets.end(),
              [](const Target &a, const Target &b)
              {
                  return a.distance < b.distance;
              });

    int count = std::min(5, (int)targets.size());

    for (int i = 0; i < count; i++)
    {
        targets[i].alien->Destroy();
    }
}