#include "GameOverMenu.hpp"
#include <cstdio>

GameOverMenu::GameOverMenu(sf::Font* f, int score, bool isVictory) 
    : font(f), titleText(*font), finalScoreText(*font), restartButton(*font), menuButton(*font) {
    
    // Tiêu đề Thắng hoặc Thua
    titleText.setCharacterSize(45);
    if (isVictory) {
        titleText.setFillColor(sf::Color::Green);
        titleText.setString("CHIEN THANG!");
    } else {
        titleText.setFillColor(sf::Color::Red);
        titleText.setString("THAT BAI");
    }
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    titleText.setPosition(sf::Vector2f(450.0f, 250.0f));

    // Điểm đạt được
    finalScoreText.setCharacterSize(28);
    finalScoreText.setFillColor(sf::Color::Yellow);
    char buf[50];
    snprintf(buf, sizeof(buf), "DIEM CUA BAN: %d", score);
    finalScoreText.setString(buf);
    bounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    finalScoreText.setPosition(sf::Vector2f(450.0f, 350.0f));

    // Nút Chơi lại
    restartButton.setCharacterSize(30);
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setString("CHOI LAI");
    bounds = restartButton.getLocalBounds();
    restartButton.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    restartButton.setPosition(sf::Vector2f(450.0f, 480.0f));

    // Nút Về Main Menu
    menuButton.setCharacterSize(30);
    menuButton.setFillColor(sf::Color::Cyan);
    menuButton.setString("VE MAN HINH CHINH");
    bounds = menuButton.getLocalBounds();
    menuButton.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    menuButton.setPosition(sf::Vector2f(450.0f, 560.0f));
}

GameOverMenu::~GameOverMenu() {}

void GameOverMenu::Update(sf::Vector2f mousePos) {
    if (restartButton.getGlobalBounds().contains(mousePos)) {
        restartButton.setScale(sf::Vector2f(1.1f, 1.1f));
        restartButton.setFillColor(sf::Color::Yellow);
    } else {
        restartButton.setScale(sf::Vector2f(1.0f, 1.0f));
        restartButton.setFillColor(sf::Color::Green);
    }

    if (menuButton.getGlobalBounds().contains(mousePos)) {
        menuButton.setScale(sf::Vector2f(1.1f, 1.1f));
        menuButton.setFillColor(sf::Color::White);
    } else {
        menuButton.setScale(sf::Vector2f(1.0f, 1.0f));
        menuButton.setFillColor(sf::Color::Cyan);
    }
}

int GameOverMenu::HandleClick(sf::Vector2f mousePos) {
    if (restartButton.getGlobalBounds().contains(mousePos)) {
        return 1; // Chơi lại
    }
    if (menuButton.getGlobalBounds().contains(mousePos)) {
        return 2; // Về Main Menu
    }
    return 0;
}

void GameOverMenu::Render(sf::RenderWindow& window) {
    // Lớp nền tối mờ
    sf::RectangleShape overlay(sf::Vector2f(900.0f, 900.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    window.draw(overlay);

    window.draw(titleText);
    window.draw(finalScoreText);
    window.draw(restartButton);
    window.draw(menuButton);
}