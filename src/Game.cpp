#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional> // Bắt buộc phải có cho SFML 3 Event

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

    resourceManager.LoadTexture("bomb", "assets/images/bomb.png");
    std::cout << "Da load xong buff bullet\n";

    resourceManager.LoadTexture("background", "assets/images/background.png");
    std::cout << "Da load xong background texture\n";
    resourceManager.LoadFont("arial", "assets/font/arial.ttf");
    std::cout << "Da load xong font\n";

    sf::Vector2f startPos(WORLD_WIDTH / 2.0f, WORLD_HEIGHT - 100.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);
    std::cout << "Da tao xong Player\n";

    currentState = GameState::Playing;
    LoadHighScore();

    backgroundSprite = new sf::Sprite(*resourceManager.GetTexture("background"));

    // Co giãn ảnh nền phủ kín WORLD (900x900)
    sf::Vector2u textureSize = resourceManager.GetTexture("background")->getSize();
    float scaleX = WORLD_WIDTH / textureSize.x;
    float scaleY = WORLD_HEIGHT / textureSize.y;
    backgroundSprite->setScale(sf::Vector2f(scaleX, scaleY));
    std::cout << "Da tao xong Background\n";

    // Thiết lập nút Restart căn chính giữa màn hình WORLD
    restartButton.setSize(sf::Vector2f(200.0f, 60.0f));
    restartButton.setFillColor(sf::Color(50, 150, 50)); // màu xanh lá
    restartButton.setOrigin(sf::Vector2f(100.0f, 30.0f));
    restartButton.setPosition(sf::Vector2f(WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f));

    restartButtonText = new sf::Text(*resourceManager.GetFont("arial"), "Choi lai", 24);
    restartButtonText->setFillColor(sf::Color::White);
    
    // Căn giữa chữ inside nút
    sf::FloatRect textBounds = restartButtonText->getLocalBounds();
    restartButtonText->setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f, 
                                              textBounds.position.y + textBounds.size.y / 2.0f));
    restartButtonText->setPosition(sf::Vector2f(WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f));
}

Game::~Game()
{
    delete player;
    delete backgroundSprite;
    delete alienManager;
    delete buffManager;       // Giữ code dọn dẹp của bạn
    delete restartButtonText; // Giữ code dọn dẹp của Vinh

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

        
        // Kết hợp logic bắn súng của bạn và logic phím Enter của Vinh
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::Playing){
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    player->Shoot(bullets, resourceManager.GetTexture("bullet"));
                }
            }
            else if(currentState == GameState::GameOver || currentState == GameState::Victory){
                if(keyPressed->code == sf::Keyboard::Key::Enter){
                    RestartGame();
                }
            }
        }

        // Click chuột vào nút của Vinh
        if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseClicked->button == sf::Mouse::Button::Left) {
                if (currentState == GameState::GameOver || currentState == GameState::Victory) {
                    sf::Vector2f mousePos(mouseClicked->position.x, mouseClicked->position.y);

                    if (restartButton.getGlobalBounds().contains(mousePos)) {
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
        
        // GIỮ CODE VA CHẠM CỦA BẠN (Vì nó chứa buffManager)
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
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);

    // 2. Chuyển lại gameView (đã có viewport) để vẽ game chính
    window.setView(gameView);

    // 3. Vẽ các thành phần của game như bình thường
    window.draw(*backgroundSprite);

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

    if (currentState == GameState::GameOver || currentState == GameState::Victory) {
        window.draw(restartButton);
        window.draw(*restartButtonText);
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
void Game::RestartGame(){
    delete player;
    sf::Vector2f startPos(400.0f, 550.0f);
    player = new Player(resourceManager.GetTexture("player"), startPos);

    for (Bullet* bullet : bullets){
        delete bullet;
    }
    bullets.clear();

    alienManager->Reset(resourceManager.GetTexture("enemy"));

    currentState = GameState::Playing;

    std::cout << "Da bat dau lai\n";
}

void Game::UpdateView() {
    float windowRatio = (float)window.getSize().x / (float)window.getSize().y;
    float worldRatio = WORLD_WIDTH / WORLD_HEIGHT;

    float sizeX = 1.0f, sizeY = 1.0f;
    float posX = 0.0f, posY = 0.0f;

    if (windowRatio > worldRatio) {
        // Cửa sổ rộng hơn tỉ lệ gốc -> thêm viền đen 2 bên trái/phải
        sizeX = worldRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        // Cửa sổ cao hơn tỉ lệ gốc -> thêm viền đen trên/dưới
        sizeY = windowRatio / worldRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    gameView.setViewport(sf::FloatRect(sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY)));
    window.setView(gameView);
}