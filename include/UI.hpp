#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameState.hpp"

class UI {
private:
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text centerText; // Dùng để hiển thị "Game Over" hoặc "Press Enter to Play"

public:
    UI(sf::Font* font);
    ~UI();

    void Update(Player* player, GameState currentState);
    void Render(sf::RenderWindow& window);
};