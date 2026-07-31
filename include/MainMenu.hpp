#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::Font* font;
    sf::Sprite* bgSprite;       
    sf::Text titleText;       
    sf::Text introText;       
    sf::Text playButton;      
    sf::Text highScoreText;   

public:
    MainMenu(sf::Font* font, sf::Texture* bgTexture, int highScore);
    ~MainMenu();

    void Update(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window);
    
    int HandleClick(sf::Vector2f mousePos);
};