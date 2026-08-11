#ifndef SHIPSELECTIONMENU_HPP
#define SHIPSELECTIONMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class ShipSelectionMenu
{
private:
    sf::Font *font;

    sf::Text titleText;
    sf::Text instructionText;
    sf::Text shipNameText;
    sf::RectangleShape frameBackground;
    sf::RectangleShape frameShape;
    sf::Sprite *shipSprite;

    std::vector<sf::Texture *> shipTextures;

    int selectedShip;

    void RefreshSelection();

public:
    ShipSelectionMenu(
        sf::Font *font,
        const std::vector<sf::Texture *> &textures);

    ~ShipSelectionMenu();

    void Render(sf::RenderWindow &window);

    void SetSelectedShip(int index);
    void MoveSelection(int delta);

    int GetSelectedShip() const;
};

#endif