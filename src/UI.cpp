#include "UI.hpp"
#include <cstdio>
#include <iostream>

UI::UI(sf::Font *f) 
    : font(f), 
      scoreText(*font), 
      shieldText(*font), 
      doubleShotText(*font), 
      titleText(*font), 
      subText(*font), 
      scoreResultText(*font), 
      currentShieldTime(0.f), 
      currentShieldHits(0), 
      hasShield(false),
      currentDoubleShotTime(0.f), 
      hasDoubleShot(false),
      currentLives(3)
{
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));

    if (!heartTexture.loadFromFile("assets/images/heart.png")) {
        std::cout << "Loi load heart.png trong UI\n";
    }
    if (!doubleShotTexture.loadFromFile("assets/images/doubleShot.png")) {
        std::cout << "Loi load doubleShot.png trong UI\n";
    }
    if (!shieldTexture.loadFromFile("assets/images/shield.png")) {
        std::cout << "Loi load shield.png trong UI\n";
    }

    // Đặt vị trí text lệch sang phải để nhường chỗ cho icon
    doubleShotText.setCharacterSize(20);
    doubleShotText.setFillColor(sf::Color::Yellow);
    doubleShotText.setPosition(sf::Vector2f(45.0f, 75.0f));

    shieldText.setCharacterSize(20);
    shieldText.setFillColor(sf::Color::Cyan);
    shieldText.setPosition(sf::Vector2f(45.0f, 110.0f));

    titleText.setCharacterSize(50);
    subText.setCharacterSize(26);
    scoreResultText.setCharacterSize(32);

    overlay.setSize(sf::Vector2f(900.0f, 900.0f));
    overlay.setFillColor(sf::Color(5, 5, 15, 240));
    overlay.setPosition(sf::Vector2f(0.0f, 0.0f));
}

UI::~UI() {}

void UI::Update(Player *player, GameState currentState, int highScore)
{
    state = currentState;
    currentLives = player->GetLives();

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Score: %d", player->GetScore());
    scoreText.setString(buffer);

    hasShield = player->HasShield();
    if (hasShield)
    {
        currentShieldTime = player->GetShieldTimer();
        currentShieldHits = player->GetShieldHitsRemaining();

        snprintf(buffer, sizeof(buffer),
                 ": %.1fs (%d Hits)",
                 currentShieldTime,
                 currentShieldHits);
        shieldText.setString(buffer);
    }

    hasDoubleShot = player->HasDoubleShot();
    if (hasDoubleShot)
    {
        currentDoubleShotTime = player->GetDoubleShotTimer();

        snprintf(buffer, sizeof(buffer),
                 ": %.1fs",
                 currentDoubleShotTime);
        doubleShotText.setString(buffer);
    }

    if (state == GameState::GameOver)
    {
        titleText.setFillColor(sf::Color::Red);
        titleText.setString("GAME OVER");

        subText.setFillColor(sf::Color(220, 220, 220));
        subText.setString("Press Enter to restart");

        scoreResultText.setFillColor(sf::Color::Cyan);
        scoreResultText.setString(scoreText.getString());
    }
    else if (state == GameState::Victory)
    {
        titleText.setFillColor(sf::Color::Green);
        titleText.setString("VICTORY!");

        subText.setFillColor(sf::Color(220, 220, 220));
        subText.setString("Press Enter to restart");

        scoreResultText.setFillColor(sf::Color::Cyan);
        scoreResultText.setString(scoreText.getString());
    }

    sf::FloatRect bounds;

    bounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y));
    titleText.setPosition(sf::Vector2f(450.0f, 320.0f));

    bounds = subText.getLocalBounds();
    subText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y));
    subText.setPosition(sf::Vector2f(450.0f, 420.0f));

    bounds = scoreResultText.getLocalBounds();
    scoreResultText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y));
    scoreResultText.setPosition(sf::Vector2f(450.0f, 500.0f));
}

void UI::Render(sf::RenderWindow &window)
{
    if (state == GameState::Playing)
    {
        window.draw(scoreText);

        // Vẽ danh sách hình trái tim thay cho chữ Lives
        for (int i = 0; i < currentLives; ++i)
        {
            sf::Sprite heartSprite(heartTexture);
            
            sf::Vector2u size = heartTexture.getSize();
            if (size.x > 0 && size.y > 0) {
                heartSprite.setScale(sf::Vector2f(25.0f / size.x, 25.0f / size.y));
            }
            
            heartSprite.setPosition(sf::Vector2f(10.0f + (i * 30.0f), 40.0f));
            window.draw(heartSprite);
        }

        // Chỉ vẽ icon và thời gian Shield khi người chơi đang có khiên
        if (hasShield)
        {
            sf::Sprite shieldSprite(shieldTexture);
            sf::Vector2u size = shieldTexture.getSize();
            if (size.x > 0 && size.y > 0) {
                shieldSprite.setScale(sf::Vector2f(25.0f / size.x, 25.0f / size.y));
            }
            shieldSprite.setPosition(sf::Vector2f(10.0f, 110.0f));
            window.draw(shieldSprite);

            window.draw(shieldText);
        }

        // Chỉ vẽ icon và thời gian Double Shot khi đang kích hoạt
        if (hasDoubleShot)
        {
            sf::Sprite doubleShotSprite(doubleShotTexture);
            sf::Vector2u size = doubleShotTexture.getSize();
            if (size.x > 0 && size.y > 0) {
                doubleShotSprite.setScale(sf::Vector2f(25.0f / size.x, 25.0f / size.y));
            }
            doubleShotSprite.setPosition(sf::Vector2f(10.0f, 75.0f));
            window.draw(doubleShotSprite);

            window.draw(doubleShotText);
        }
    }
    else if (state == GameState::GameOver || state == GameState::Victory)
    {
        window.draw(overlay);
        window.draw(titleText);
        window.draw(subText);
        window.draw(scoreResultText);
    }
}