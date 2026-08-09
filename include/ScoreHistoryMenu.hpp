#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class ScoreHistoryMenu {
private:
    sf::Font* font;
    sf::RectangleShape backgroundOverlay;
    
    std::unique_ptr<sf::Texture> menuBgTexture;
    std::unique_ptr<sf::Sprite> menuBgSprite;

    sf::Text titleText;
    
    // Biến ảnh cho nút Back
    std::unique_ptr<sf::Texture> backTexture;
    std::unique_ptr<sf::Sprite> backSprite;

    std::vector<sf::Text> scoreTexts;

public:
    ScoreHistoryMenu(sf::Font* font, const std::vector<int>& recentScores);
    ~ScoreHistoryMenu() = default;

    ScoreHistoryMenu(const ScoreHistoryMenu&) = delete;
    ScoreHistoryMenu& operator=(const ScoreHistoryMenu&) = delete;

    void Update(sf::Vector2f mousePos);
    bool IsBackButtonClicked(sf::Vector2f mousePos) const;
    void Render(sf::RenderWindow& window);
};