#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameOverMenu {
private:
    sf::Font* font;
    
    std::unique_ptr<sf::Texture> titleTexture;
    std::unique_ptr<sf::Sprite> titleSprite;

    sf::Text finalScoreText;

    // Thay thế nút chữ bằng Texture và Sprite
    std::unique_ptr<sf::Texture> restartTexture;
    std::unique_ptr<sf::Sprite> restartSprite;

    std::unique_ptr<sf::Texture> menuTexture;
    std::unique_ptr<sf::Sprite> menuSprite;

public:
    GameOverMenu(sf::Font* f, int score, bool isVictory);
    ~GameOverMenu() = default;

    GameOverMenu(const GameOverMenu&) = delete;
    GameOverMenu& operator=(const GameOverMenu&) = delete;

    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window);
};