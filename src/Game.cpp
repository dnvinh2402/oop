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

    sf::Vector2f startPos(400.0f, 550.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);
    std::cout << "Da tao xong Player\n";

    currentState = GameState::Playing;
    LoadHighScore();

    backgroundSprite = new sf::Sprite(*resourceManager.GetTexture("background"));

    shieldSprite = new sf::Sprite(*resourceManager.GetTexture("shield_effect"));
    sf::Vector2u size = resourceManager.GetTexture("shield_effect")->getSize();

    shieldSprite->setScale(sf::Vector2f(64.f / size.x, 64.f / size.y));

    // Co giãn ảnh nền cho vừa khít cửa sổ 800x600
    sf::Vector2u textureSize = resourceManager.GetTexture("background")->getSize();
    float scaleX = 800.0f / textureSize.x;
    float scaleY = 600.0f / textureSize.y;
    backgroundSprite->setScale(sf::Vector2f(scaleX, scaleY));
    std::cout << "Da tao xong Background\n";

    restartButton.setSize(sf::Vector2f(200.0f, 60.0f));
    restartButton.setFillColor(sf::Color(50, 150, 50));
    restartButton.setPosition(sf::Vector2f(300.0f, 350.0f));

    restartButtonText = new sf::Text(*resourceManager.GetFont("arial"), "Choi lai", 24);
    restartButtonText->setFillColor(sf::Color::White);
    restartButtonText->setPosition(sf::Vector2f(330.0f, 365.0f)); // canh giữa trong nút
}

Game::~Game()
{
    delete player;
    delete backgroundSprite;
    delete alienManager;
    delete buffManager;
    delete restartButtonText;
    delete explosionSprite;
    delete shieldSprite;

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

        // Xử lý khi cửa sổ bị kéo giãn (Ép giữ tỉ lệ khung hình thật của cửa sổ)
        if (const auto *resized = event->getIf<sf::Event::Resized>())
        {
            // 1. Lấy chiều rộng mới mà người dùng vừa kéo
            unsigned int newWidth = resized->size.x;

            // 2. Ép chiều cao phải chạy theo đúng tỉ lệ 4:3 (vì game của bạn là 800x600)
            unsigned int newHeight = (newWidth * 3) / 4;

            // 3. Nếu người dùng kéo lệch tỉ lệ, ta ra lệnh cho cửa sổ tự động snap (co/giãn) về đúng tỉ lệ
            if (resized->size.y != newHeight)
            {
                window.setSize({newWidth, newHeight});
            }

            // 4. Cập nhật lại camera ảo để hình ảnh bên trong luôn giữ gốc 800x600 sắc nét
            sf::View view({400.0f, 300.0f}, {800.0f, 600.0f});
            window.setView(view);
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (currentState == GameState::Playing)
            {
                if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    player->Shoot(bullets, resourceManager.GetTexture("bullet"));
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

        if (const auto *mouseClicked = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseClicked->button == sf::Mouse::Button::Left)
            {
                if (currentState == GameState::GameOver || currentState == GameState::Victory)
                {
                    sf::Vector2f mousePos(mouseClicked->position.x, mouseClicked->position.y);

                    if (restartButton.getGlobalBounds().contains(mousePos))
                    {
                        RestartGame();
                    }
                }
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
            sf::FloatRect playerBounds = player->GetBounds();

            sf::Vector2u missileSize =
                resourceManager.GetTexture("missile")->getSize();

            sf::Vector2f pos;

            pos.x = playerBounds.position.x + playerBounds.size.x / 2.f - missileSize.x / 2.f;

            pos.y = playerBounds.position.y - missileSize.y;

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

                    // Tiêu diệt 5 Alien gần nhất
                    DestroyNearestAliens(missile->GetPosition());

                    // Hiện hiệu ứng nổ
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
            {
                explosionActive = false;
            }
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
    // Bôi màu nền xám giống hệt file main cũ của bạn
    window.clear(sf::Color(127, 127, 127));

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
    {
        missile->Render(window);
    }
    if (explosionActive)
    {
        window.draw(*explosionSprite);
    }

    for (Bullet *bullet : bullets)
    {
        bullet->Render(window);
    }

    if (currentState == GameState::GameOver || currentState == GameState::Victory)
    {
        window.draw(restartButton);
        window.draw(*restartButtonText);
    }
    if (explosionActive)
    {
        window.draw(*explosionSprite);
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

// Giữ lại hàm tạo nổ lan của Bạn
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

// Giữ lại hàm Khởi động lại game của Vinh
void Game::RestartGame()
{
    delete player;
    sf::Vector2f startPos(400.0f, 550.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);

    for (Bullet *bullet : bullets)
    {
        delete bullet;
    }
    bullets.clear();

    alienManager->Reset(resourceManager.GetTexture("enemy"));

    currentState = GameState::Playing;

    std::cout << "Da bat dau lai\n";
}