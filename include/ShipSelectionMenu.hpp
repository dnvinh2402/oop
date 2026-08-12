#ifndef SHIPSELECTIONMENU_HPP
#define SHIPSELECTIONMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ShipSelectionMenu
{
private:
    sf::Font *font;

    // =========================
    // TEXT
    // =========================

    sf::Text titleText;
    sf::Text instructionText;
    sf::Text shipNameText;
    sf::Text shipCountText;
    sf::Text attributesText;

    sf::Text healthIcon;
    sf::Text fireRateIcon;
    sf::Text speedIcon;

    // =========================
    // SHIP
    // =========================

    sf::Sprite *shipSprite;

    std::vector<sf::Texture *> shipTextures;

    int selectedShip;

    // =========================
    // FRAME
    // =========================

    sf::RectangleShape frameBackground;
    sf::RectangleShape frameShape;

    // =========================
    // STATIC ATTRIBUTE VALUES
    // =========================

    int healthLevel;
    int fireRateLevel;
    int speedLevel;

    std::string shipName;

    // =========================
    // FUNCTIONS
    // =========================

    void RefreshSelection();

    void DrawStatBar(
        sf::RenderWindow &window,
        float x,
        float y,
        int currentLevel,
        int maxLevel = 12);

public:
    ShipSelectionMenu(
        sf::Font *font,
        const std::vector<sf::Texture *> &textures);

    ~ShipSelectionMenu();

    void Update();
    void Render(sf::RenderWindow &window);
    void UpdateAnimation(float deltaTime);

    void SetSelectedShip(int index);
    void MoveSelection(int delta);

    int GetSelectedShip() const;

    int GetHealthLevel() const;
    int GetFireRateLevel() const;
    int GetSpeedLevel() const;
};

#endif