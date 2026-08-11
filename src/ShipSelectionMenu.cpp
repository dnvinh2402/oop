#include "ShipSelectionMenu.hpp"
#include <string>

ShipSelectionMenu::ShipSelectionMenu(
    sf::Font *font,
    const std::vector<sf::Texture *> &textures)
    : font(font),
      titleText(*font),
      instructionText(*font),
      shipNameText(*font),
      shipTextures(textures),
      selectedShip(0),
      shipSprite(nullptr)
{
    // =========================
    // TITLE
    // =========================
    titleText.setString("SELECT YOUR SHIP");
    titleText.setCharacterSize(45);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = titleText.getLocalBounds();

    titleText.setOrigin(
        sf::Vector2f(
            titleBounds.position.x + titleBounds.size.x / 2.f,
            titleBounds.position.y));

    titleText.setPosition(
        sf::Vector2f(450.f, 100.f));

    // ve khung cho menu phi thuyen
    frameBackground.setSize(sf::Vector2f(300.f, 250.f));

    frameBackground.setFillColor(sf::Color(8, 15, 35)); // xanh đậm gần đen

    frameBackground.setPosition(sf::Vector2f(300.f, 270.f));

    frameShape.setSize(sf::Vector2f(300.f, 250.f));
    frameShape.setFillColor(sf::Color::Transparent);
    frameShape.setOutlineColor(sf::Color::Cyan);
    frameShape.setOutlineThickness(4.f);

    frameShape.setPosition(sf::Vector2f(300.f, 270.f));
    // =========================
    // INSTRUCTION
    // =========================
    instructionText.setString(
        "<- / -> SELECT     ENTER START     ESC BACK");

    instructionText.setCharacterSize(18);
    instructionText.setFillColor(
        sf::Color(220, 220, 220));

    sf::FloatRect instructionBounds =
        instructionText.getLocalBounds();

    instructionText.setOrigin(
        sf::Vector2f(
            instructionBounds.position.x +
                instructionBounds.size.x / 2.f,
            instructionBounds.position.y));

    instructionText.setPosition(
        sf::Vector2f(450.f, 750.f));

    // =========================
    // SHIP NAME
    // =========================
    shipNameText.setCharacterSize(25);
    shipNameText.setFillColor(sf::Color::Cyan);

    shipNameText.setString("SHIP 1 / " +
                           std::to_string(shipTextures.size()));

    // =========================
    // CREATE SHIP
    // =========================
    RefreshSelection();
}

ShipSelectionMenu::~ShipSelectionMenu()
{
    delete shipSprite;
}

void ShipSelectionMenu::RefreshSelection()
{
    if (shipSprite != nullptr)
    {
        delete shipSprite;
        shipSprite = nullptr;
    }

    if (shipTextures.empty())
    {
        shipNameText.setString("NO SHIP");
        return;
    }

    shipSprite =
        new sf::Sprite(*shipTextures[selectedShip]);

    // =========================
    // SCALE SHIP
    // =========================
    sf::Vector2u size =
        shipTextures[selectedShip]->getSize();

    if (size.x > 0 && size.y > 0)
    {
        float scale =
            120.f / static_cast<float>(size.x);

        shipSprite->setScale(
            sf::Vector2f(scale, scale));
    }

    // =========================
    // CENTER ORIGIN
    // =========================
    sf::FloatRect bounds =
        shipSprite->getLocalBounds();

    shipSprite->setOrigin(
        sf::Vector2f(
            bounds.position.x +
                bounds.size.x / 2.f,
            bounds.position.y +
                bounds.size.y / 2.f));

    // =========================
    // SHIP POSITION
    // =========================
    shipSprite->setPosition(
        sf::Vector2f(450.f, 400.f));

    // =========================
    // SHIP NAME
    // =========================
    shipNameText.setString(
        "SHIP " +
        std::to_string(selectedShip + 1) +
        " / " +
        std::to_string(shipTextures.size()));

    sf::FloatRect nameBounds =
        shipNameText.getLocalBounds();

    shipNameText.setOrigin(
        sf::Vector2f(
            nameBounds.position.x +
                nameBounds.size.x / 2.f,
            nameBounds.position.y));

    shipNameText.setPosition(
        sf::Vector2f(450.f, 550.f));
}

void ShipSelectionMenu::SetSelectedShip(int index)
{
    if (shipTextures.empty())
        return;

    int count =
        static_cast<int>(shipTextures.size());

    selectedShip = index % count;

    if (selectedShip < 0)
        selectedShip += count;

    RefreshSelection();
}

void ShipSelectionMenu::MoveSelection(int delta)
{
    SetSelectedShip(selectedShip + delta);
}

int ShipSelectionMenu::GetSelectedShip() const
{
    return selectedShip;
}

void ShipSelectionMenu::Render(
    sf::RenderWindow &window)
{
    window.draw(titleText);
    window.draw(frameBackground);

    if (shipSprite != nullptr)
        window.draw(*shipSprite);
    window.draw(frameShape);
    window.draw(shipNameText);
    window.draw(instructionText);
}