#include "ScoreHistoryMenu.hpp"

ScoreHistoryMenu::ScoreHistoryMenu(sf::Font* f, const std::vector<int>& recentScores) 
    : font(f), 
      titleText(*f, "MATCH HISTORY", 28), 
      backButton(*f, "Back", 22) 
{
    backgroundOverlay.setSize(sf::Vector2f(900.0f, 900.0f));
    backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 200));

    menuBox.setSize(sf::Vector2f(450.0f, 400.0f));
    menuBox.setFillColor(sf::Color(20, 20, 35, 240));
    menuBox.setOutlineColor(sf::Color::Cyan);
    menuBox.setOutlineThickness(2.0f);
    menuBox.setPosition(sf::Vector2f(225.0f, 250.0f));

    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(sf::Vector2f(340.0f, 280.0f));

    backButton.setFillColor(sf::Color::White);
    backButton.setPosition(sf::Vector2f(420.0f, 570.0f));

    // Hiển thị tối đa 5 trận gần nhất
    float startY = 340.0f;
    for (size_t i = 0; i < 5; ++i) {
        sf::Text rowText(*font, "", 20);
        rowText.setFillColor(sf::Color::White);
        
        char buf[64];
        if (i < recentScores.size()) {
            std::snprintf(buf, sizeof(buf), "%d. Match %zu:  %d pts", (int)(i + 1), i + 1, recentScores[i]);
        } else {
            std::snprintf(buf, sizeof(buf), "%d. Match %zu:  ---", (int)(i + 1), i + 1);
        }
        rowText.setString(buf);
        rowText.setPosition(sf::Vector2f(280.0f, startY + (i * 35.0f)));
        scoreTexts.push_back(rowText);
    }
}

ScoreHistoryMenu::~ScoreHistoryMenu() {}

void ScoreHistoryMenu::Update(sf::Vector2f mousePos) {
    if (backButton.getGlobalBounds().contains(mousePos)) {
        backButton.setFillColor(sf::Color::Yellow);
    } else {
        backButton.setFillColor(sf::Color::White);
    }
}

bool ScoreHistoryMenu::IsBackButtonClicked(sf::Vector2f mousePos) const {
    return backButton.getGlobalBounds().contains(mousePos);
}

void ScoreHistoryMenu::Render(sf::RenderWindow& window) {
    window.draw(backgroundOverlay);
    window.draw(menuBox);
    window.draw(titleText);
    window.draw(backButton);

    for (const auto& text : scoreTexts) {
        window.draw(text);
    }
}