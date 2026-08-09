#include "GameOverMenu.hpp"
#include <cstdio>
#include <iostream>

GameOverMenu::GameOverMenu(sf::Font* f, int score, bool isVictory) 
    : font(f), finalScoreText(*font) {
    
    // 1. Tải ảnh Victory hoặc Defeat
    titleTexture = new sf::Texture();
    if (isVictory) {
        if (!titleTexture->loadFromFile("assets/images/victory.png")) {
            std::cout << "Loi load victory.png\n";
        }
    } else {
        if (!titleTexture->loadFromFile("assets/images/defeat.png")) {
            std::cout << "Loi load defeat.png\n";
        }
    }
    
    titleSprite = new sf::Sprite(*titleTexture);

    // Thu nhỏ logo
    sf::Vector2u texSize = titleTexture->getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        float targetWidth = 350.0f; 
        float scale = targetWidth / texSize.x;
        titleSprite->setScale(sf::Vector2f(scale, scale));
    }

    // Vị trí logo
    sf::FloatRect bounds = titleSprite->getLocalBounds();
    titleSprite->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    titleSprite->setPosition(sf::Vector2f(450.0f, 350.0f));

    // Điểm đạt được
    finalScoreText.setCharacterSize(26);
    finalScoreText.setFillColor(sf::Color::Yellow);
    char buf[50];
    snprintf(buf, sizeof(buf), "SCORE: %d", score);
    finalScoreText.setString(buf);
    sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin(sf::Vector2f(scoreBounds.position.x + scoreBounds.size.x / 2.0f, scoreBounds.position.y + scoreBounds.size.y / 2.0f));
    finalScoreText.setPosition(sf::Vector2f(450.0f, 480.0f));

    // 2. Tải ảnh nút
    restartTexture = new sf::Texture();
    menuTexture = new sf::Texture();
    if (!restartTexture->loadFromFile("assets/images/play_again.png")) std::cout << "Loi load play_again.png\n";
    if (!menuTexture->loadFromFile("assets/images/main_menu.png")) std::cout << "Loi load main_menu.png\n";

    restartSprite = new sf::Sprite(*restartTexture);
    menuSprite = new sf::Sprite(*menuTexture);

    // Hàm thiết lập nút
    auto setupButtonSprite = [](sf::Sprite* sprite, sf::Texture* tex, float targetWidth, sf::Vector2f pos) {
        sf::Vector2u size = tex->getSize();
        if (size.x > 0 && size.y > 0) {
            float scale = targetWidth / size.x;
            sprite->setScale(sf::Vector2f(scale, scale));
        }
        sf::FloatRect b = sprite->getLocalBounds();
        sprite->setOrigin(sf::Vector2f(b.position.x + b.size.x / 2.0f, b.position.y + b.size.y / 2.0f));
        sprite->setPosition(pos);
    };

    setupButtonSprite(restartSprite, restartTexture, 75.0f, sf::Vector2f(380.0f, 650.0f));
    setupButtonSprite(menuSprite, menuTexture, 70.0f, sf::Vector2f(520.0f, 650.0f));
}

GameOverMenu::~GameOverMenu() {
    delete titleSprite;
    delete titleTexture;
    delete restartSprite;
    delete restartTexture;
    delete menuSprite;
    delete menuTexture;
}

void GameOverMenu::Update(sf::Vector2f mousePos) {
    auto hoverEffect = [&](sf::Sprite* spr) {
        if (spr->getGlobalBounds().contains(mousePos)) {
            spr->setColor(sf::Color(255, 255, 255, 120)); 
        } else {
            spr->setColor(sf::Color(255, 255, 255, 255)); 
        }
    };

    hoverEffect(restartSprite);
    hoverEffect(menuSprite);
}

int GameOverMenu::HandleClick(sf::Vector2f mousePos) {
    if (restartSprite->getGlobalBounds().contains(mousePos)) {
        return 1; 
    }
    if (menuSprite->getGlobalBounds().contains(mousePos)) {
        return 2; 
    }
    return 0;
}

void GameOverMenu::Render(sf::RenderWindow& window) {
    sf::RectangleShape overlay(sf::Vector2f(900.0f, 900.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    window.draw(overlay);

    window.draw(*titleSprite);
    window.draw(finalScoreText);
    window.draw(*restartSprite);
    window.draw(*menuSprite);
}