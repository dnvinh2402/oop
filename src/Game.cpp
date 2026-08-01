#include "Game.hpp"
#include "MainMenu.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>

const float WORLD_WIDTH = 900.0f;
const float WORLD_HEIGHT = 900.0f;

Game::Game() : window(sf::VideoMode({900, 900}), "My first game", sf::Style::Default | sf::Style::Resize)
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

    sf::Vector2f startPos(WORLD_WIDTH / 2.0f, WORLD_HEIGHT - 100.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);
    std::cout << "Da tao xong Player\n";

    currentState = GameState::MainMenu;
    LoadHighScore();

    gameUI = new UI(resourceManager.GetFont("arial"));
    
    mainMenu = new MainMenu(resourceManager.GetFont("arial"), resourceManager.GetTexture("background"), highScore);

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

        // Bắt sự kiện di chuyển chuột ở MainMenu
        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            if (currentState == GameState::MainMenu) {
                mainMenu->Update(sf::Vector2f(mouseMoved->position.x, mouseMoved->position.y));
            }
        }

        // Bắt sự kiện từ bàn phím
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::Playing){
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    player->Shoot(bullets, resourceManager.GetTexture("bullet"));
                }
            }
            else if (currentState == GameState::MainMenu) {
                if(keyPressed->code == sf::Keyboard::Key::Enter){
                    currentState = GameState::Playing; 
                }
            }
            // CHỈ CHO PHÉP NHẤN ENTER ĐỂ CHƠI LẠI KHI THUA HOẶC THẮNG
            else if(currentState == GameState::GameOver || currentState == GameState::Victory){
                if(keyPressed->code == sf::Keyboard::Key::Enter){
                    RestartGame();
                }
            }
        }

        // Bắt sự kiện từ chuột (Đã loại bỏ hoàn toàn việc click chuột để restart ở màn hình kết thúc)
        if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (currentState == GameState::Playing) {
                if (mouseClicked->button == sf::Mouse::Button::Right || mouseClicked->button == sf::Mouse::Button::Left) {
                    player->Shoot(bullets, resourceManager.GetTexture("bullet"));
                }
            }
            else if (currentState == GameState::MainMenu) {
                if (mouseClicked->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(mouseClicked->position.x, mouseClicked->position.y);
                    int action = mainMenu->HandleClick(mousePos);
                    if (action == 1) {
                        currentState = GameState::Playing; 
                    }
                    else if (action == 2) {
                        std::cout << "--> Xem diem cao: " << highScore << "\n";
                    }
                }
            }
            // Ở trạng thái GameOver hoặc Victory, click chuột không làm gì cả
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
                    missile->Destroy();
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
        else if (alienManager->IsRoundCleared())
        {
            if (alienManager->IsFinalRound())
            {
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
                alienManager->StartNextRound(resourceManager.GetTexture("enemy"));
                std::cout << "Chuyen sang Round " << alienManager->GetCurrentRound() << "!\n";
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

    if (currentState == GameState::MainMenu) {
        mainMenu->Render(window);
    }
    else {
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
        
        for (Bullet *bullet : bullets)
        {
            bullet->Render(window);
        }

        if (explosionActive)
        {
            window.draw(*explosionSprite);
        }

        gameUI->Render(window);
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
        t.distance = dx * dx + dy * dy;

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