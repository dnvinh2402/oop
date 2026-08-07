#pragma once
#include <SFML/Graphics.hpp>

class GameOverMenu {
private:
    sf::Font* font;
    
    sf::Texture* titleTexture;
    sf::Sprite* titleSprite;

    sf::Text finalScoreText;

    // Thay thế nút chữ bằng Texture và Sprite
    sf::Texture* restartTexture;
    sf::Sprite* restartSprite;

    sf::Texture* menuTexture;
    sf::Sprite* menuSprite;

public:
    GameOverMenu(sf::Font* f, int score, bool isVictory);
    ~GameOverMenu();

    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window);
};