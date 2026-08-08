#include "ScoreHistoryMenu.hpp"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>

ScoreHistoryMenu::ScoreHistoryMenu(sf::Font *f, const std::vector<int> &recentScores)
    : font(f),
      titleText(*f, "MATCH HISTORY", 26)
{
    // 1. Lớp nền mờ che không gian game phía sau
    backgroundOverlay.setSize(sf::Vector2f(900.0f, 900.0f));
    backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 160));

    // 2. Tải file ảnh historymenu.png
    menuBgTexture = new sf::Texture();
    if (!menuBgTexture->loadFromFile("assets/images/historymenu.png"))
    {
        std::cout << "Loi load historymenu.jpg trong ScoreHistoryMenu\n";
    }
    menuBgSprite = new sf::Sprite(*menuBgTexture);

    // Thiết lập kích thước khung (Ngang 600, Cao 560)
    sf::Vector2u bgSize = menuBgTexture->getSize();
    if (bgSize.x > 0 && bgSize.y > 0)
    {
        menuBgSprite->setScale(sf::Vector2f(600.0f / bgSize.x, 560.0f / bgSize.y));
    }
    sf::FloatRect bgBounds = menuBgSprite->getLocalBounds();
    menuBgSprite->setOrigin(sf::Vector2f(bgBounds.position.x + bgBounds.size.x / 2.0f, bgBounds.position.y + bgBounds.size.y / 2.0f));
    menuBgSprite->setPosition(sf::Vector2f(450.0f, 450.0f));

    // 3. Tiêu đề
    titleText.setFillColor(sf::Color(220, 100, 255));
    sf::FloatRect tBounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(tBounds.position.x + tBounds.size.x / 2.0f, tBounds.position.y + tBounds.size.y / 2.0f));
    titleText.setPosition(sf::Vector2f(450.0f, 315.0f));

    // 4. Danh sách điểm số (Đã đồng bộ hiển thị "0 pts" thay vì "---")
    float startY = 370.0f;

    size_t bestIndex = 0;
    if (!recentScores.empty())
    {
        bestIndex = std::distance(
            recentScores.begin(),
            std::max_element(recentScores.begin(), recentScores.end()));
    }
    for (size_t i = 0; i < 5; ++i)
    {
        sf::Text rowText(*font, "", 18);

        if (i < recentScores.size() &&
            recentScores[i] == *std::max_element(recentScores.begin(), recentScores.end()))
        {
            rowText.setFillColor(sf::Color(255, 220, 100));
        }
        else
        {
            rowText.setFillColor(sf::Color(220, 205, 245));
        }

        char buf[64];
        if (i < recentScores.size())
        {
            std::snprintf(buf, sizeof(buf), "Match %zu:   %d pts", i + 1, recentScores[i]);
        }
        else
        {
            std::snprintf(buf, sizeof(buf), "Match %zu:   0 pts", i + 1);
        }
        rowText.setString(buf);

        sf::FloatRect rowBounds = rowText.getLocalBounds();
        rowText.setOrigin(sf::Vector2f(rowBounds.position.x + rowBounds.size.x / 2.0f, rowBounds.position.y));
        rowText.setPosition(sf::Vector2f(450.0f, startY + (i * 32.0f)));
        scoreTexts.push_back(rowText);
    }

    // 5. Tải ảnh nút Back (back.png) ở dưới cùng
    backTexture = new sf::Texture();
    if (!backTexture->loadFromFile("assets/images/back.png"))
    {
        std::cout << "Loi load back.png trong ScoreHistoryMenu\n";
    }
    backSprite = new sf::Sprite(*backTexture);

    sf::Vector2u backSize = backTexture->getSize();
    if (backSize.x > 0 && backSize.y > 0)
    {
        backSprite->setScale(sf::Vector2f(50.0f / backSize.x, 50.0f / backSize.y));
    }
    sf::FloatRect bBounds = backSprite->getLocalBounds();
    backSprite->setOrigin(sf::Vector2f(bBounds.position.x + bBounds.size.x / 2.0f, bBounds.position.y + bBounds.size.y / 2.0f));
    backSprite->setPosition(sf::Vector2f(450.0f, 610.0f));
}

ScoreHistoryMenu::~ScoreHistoryMenu()
{
    delete menuBgSprite;
    delete menuBgTexture;
    delete backSprite;
    delete backTexture;
}

void ScoreHistoryMenu::Update(sf::Vector2f mousePos)
{
    if (backSprite->getGlobalBounds().contains(mousePos))
    {
        backSprite->setColor(sf::Color(255, 255, 255, 120));
    }
    else
    {
        backSprite->setColor(sf::Color(255, 255, 255, 255));
    }
}

bool ScoreHistoryMenu::IsBackButtonClicked(sf::Vector2f mousePos) const
{
    return backSprite->getGlobalBounds().contains(mousePos);
}

void ScoreHistoryMenu::Render(sf::RenderWindow &window)
{
    window.draw(backgroundOverlay);
    window.draw(*menuBgSprite);
    window.draw(titleText);
    window.draw(*backSprite);

    for (const auto &text : scoreTexts)
    {
        window.draw(text);
    }
}