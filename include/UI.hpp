#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Player.hpp"

class UI {
private:
    sf::Font* font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text shieldText; 
    
    // Các biến lưu trạng thái khiên để vẽ trong Render
    bool showShieldInfo;
    float currentShieldTime;
    int currentShieldHits;

    sf::Text titleText;
    sf::Text subText;
    sf::Text scoreResultText;
    
    sf::RectangleShape overlay;
    GameState state;

public:
    UI(sf::Font* font);
    ~UI();

    void Update(Player* player, GameState currentState, int highScore);
    void Render(sf::RenderWindow& window);
};