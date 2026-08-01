#pragma once
#include <SFML/Graphics.hpp>

class GameOverMenu {
private:
    sf::Font* font;
    sf::Text titleText;
    sf::Text finalScoreText;
    sf::Text restartButton;
    sf::Text menuButton;

public:
    GameOverMenu(sf::Font* f, int score, bool isVictory);
    ~GameOverMenu();

    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos); // Trả về 1: Chơi lại, 2: Về Main Menu
    void Render(sf::RenderWindow& window);
};