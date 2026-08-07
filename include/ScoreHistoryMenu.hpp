#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ScoreHistoryMenu {
private:
    sf::Font* font;
    sf::RectangleShape backgroundOverlay;
    
    sf::Texture* menuBgTexture;
    sf::Sprite* menuBgSprite;

    sf::Text titleText;
    
    // Biến ảnh cho nút Back
    sf::Texture* backTexture;
    sf::Sprite* backSprite;

    std::vector<sf::Text> scoreTexts;

public:
    ScoreHistoryMenu(sf::Font* font, const std::vector<int>& recentScores);
    ~ScoreHistoryMenu();

    void Update(sf::Vector2f mousePos);
    bool IsBackButtonClicked(sf::Vector2f mousePos) const;
    void Render(sf::RenderWindow& window);
};