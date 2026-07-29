#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <optional> // Bắt buộc phải có cho SFML 3 Event

// Khởi tạo cửa sổ y hệt code cũ của bạn
Game::Game() : window(sf::VideoMode({800, 600}), "My first game") {
    
    resourceManager.LoadTexture("player", "assets/images/player.png");
    std::cout << "Da load xong player texture\n";

    resourceManager.LoadTexture("enemy", "assets/images/enemy.png");
    
    // Khởi tạo nhạc trưởng và sinh ra bầy quái
    alienManager = new AlienManager();
    alienManager->InitializeSwarm(resourceManager.GetTexture("enemy"));

    resourceManager.LoadTexture("bullet", "assets/images/bullet.png");
    std::cout << "Da load xong bullet texture\n";
    resourceManager.LoadTexture("alien_bullet", "assets/images/alien_bullet.png");
    std::cout << "Da load xong alien bullet texture\n";

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

    // Thiết lập nút Restart
    restartButton.setSize(sf::Vector2f(200.0f, 60.0f));
    restartButton.setFillColor(sf::Color(50, 150, 50)); // màu xanh lá
    restartButton.setPosition(sf::Vector2f(300.0f, 350.0f)); // giữa màn hình

    restartButtonText = new sf::Text(*resourceManager.GetFont("arial"), "Choi lai", 24);
    restartButtonText->setFillColor(sf::Color::White);
    restartButtonText->setPosition(sf::Vector2f(330.0f, 365.0f)); // canh giữa trong nút
}

Game::~Game() {
    delete player;
    delete backgroundSprite;
    delete alienManager; 
    delete restartButtonText;

    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void Game::ProcessEvents() {
    std::optional<sf::Event> event;
    while (event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

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

void Game::Update(float deltaTime) {
    if (currentState == GameState::Playing) {
        player->Update(deltaTime);
        alienManager->Update(deltaTime);\

        for (Bullet* bullet : bullets) {
            bullet->Update(deltaTime);
        }

        alienManager->AlienShoot(bullets, resourceManager.GetTexture("alien_bullet"));
        collisionManager.CheckCollisions(player, alienManager->GetAliens(), bullets);

        CleanUpDeadEntities();

        // Kiểm tra Player còn sống không
        if (!player->IsActive()) {
            currentState = GameState::GameOver;
            if (player->GetScore() > highScore) {
                highScore = player->GetScore();
                SaveHighScore();
                std::cout << "KY LUC MOI! Diem: " << highScore << "\n";
            } else {
                std::cout << "Game Over. Diem: " << player->GetScore() << " | Ky luc: " << highScore << "\n";
            }
        }
        // Kiểm tra đợt quái hiện tại đã bị tiêu diệt hết chưa
        else if (alienManager->IsRoundCleared()) {
            if (alienManager->IsFinalRound()) {
                // Đã dẹp sạch đợt cuối cùng -> Thắng game
                currentState = GameState::Victory;
                if (player->GetScore() > highScore) {
                    highScore = player->GetScore();
                    SaveHighScore();
                }
                std::cout << "CHIEN THANG! Diem cuoi cung: " << player->GetScore() << "\n";
            } else {
                // Còn round tiếp theo -> chuyển sang đợt mới mạnh hơn
                alienManager->StartNextRound(resourceManager.GetTexture("enemy"));
                std::cout << "Chuyen sang Round " << alienManager->GetCurrentRound() << "!\n";
            }
        }
    }
}

void Game::CleanUpDeadEntities() {
    for (int i = bullets.size() - 1; i >= 0; i--) {
        if (!bullets[i]->IsActive()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Game::Render() {
    // Bôi màu nền xám giống hệt file main cũ của bạn
    window.clear(sf::Color(127, 127, 127));

    window.draw(*backgroundSprite); 
    player->Render(window);
    alienManager->Render(window);

    for (Bullet* bullet : bullets) {
        bullet->Render(window);
    }

    if (currentState == GameState::GameOver || currentState == GameState::Victory) {
        window.draw(restartButton);
        window.draw(*restartButtonText);
    }

    window.display();
}

void Game::Run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Game::LoadHighScore(){
    std::ifstream file ("highscore.txt");
    if(file.is_open()){
        file >> highScore;
        file.close();
    }
    else{
        highScore = 0;
    }
}
void Game::SaveHighScore(){
    std::ofstream file("highscore.txt");
    if(file.is_open()){
        file << highScore;
        file.close();
    }
}

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