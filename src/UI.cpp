#include "UI.hpp"
#include <cstdio>

UI::UI(sf::Font *f) : font(f), scoreText(*font), livesText(*font), shieldText(*font), doubleShotText(*font), titleText(*font), subText(*font), scoreResultText(*font), currentShieldTime(0.f), currentShieldHits(0), currentDoubleShotTime(0.f)
{

    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));

    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Red);
    livesText.setPosition(sf::Vector2f(10.0f, 40.0f));

    doubleShotText.setCharacterSize(20);
    doubleShotText.setFillColor(sf::Color::Yellow);
    doubleShotText.setPosition(sf::Vector2f(10.0f, 70.0f));

    shieldText.setCharacterSize(20);
    shieldText.setFillColor(sf::Color::Cyan);
    shieldText.setPosition(sf::Vector2f(10.0f, 100.0f));

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

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Score: %d", player->GetScore());
    scoreText.setString(buffer);

    snprintf(buffer, sizeof(buffer), "Lives: %d", player->GetLives());
    livesText.setString(buffer);

    // Lưu lại trạng thái khiên để dùng trong Render
    if (player->HasShield())
    {
        currentShieldTime = player->GetShieldTimer();
        currentShieldHits = player->GetShieldHitsRemaining();

        snprintf(buffer, sizeof(buffer),
                 "Shield      : %.1fs (%d Hits)",
                 currentShieldTime,
                 currentShieldHits);
    }
    else
    {
        snprintf(buffer, sizeof(buffer),
                 "Shield      : OFF");
    }

    shieldText.setString(buffer);

    if (player->HasDoubleShot())
    {
        currentDoubleShotTime = player->GetDoubleShotTimer();

        snprintf(buffer, sizeof(buffer),
                 "Double Shot : %.1fs",
                 currentDoubleShotTime);
    }
    else
    {
        snprintf(buffer, sizeof(buffer),
                 "Double Shot : OFF");
    }

    doubleShotText.setString(buffer);

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
        window.draw(livesText);

        window.draw(shieldText);
        window.draw(doubleShotText);
    }
    else if (state == GameState::GameOver || state == GameState::Victory)
    {
        window.draw(overlay);
        window.draw(titleText);
        window.draw(subText);
        window.draw(scoreResultText);
    }
}