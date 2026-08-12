#include "ShipSelectionMenu.hpp"
#include <iostream>
#include <algorithm>

// CONSTRUCTOR
ShipSelectionMenu::ShipSelectionMenu(
    sf::Font *font,
    const std::vector<sf::Texture *> &textures)
    : font(font),
      titleText(*font),
      instructionText(*font),
      shipNameText(*font),
      shipCountText(*font),
      attributesText(*font),
      healthIcon(*font),
      fireRateIcon(*font),
      speedIcon(*font),
      shipTextures(textures),
      selectedShip(0),
      healthLevel(10),
      fireRateLevel(8),
      speedLevel(10),
      shipName("LION")
{
    // TITLE

    titleText.setString("SELECT YOUR SHIP");
    titleText.setCharacterSize(45);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds =
        titleText.getLocalBounds();

    titleText.setOrigin(
        sf::Vector2f(
            titleBounds.position.x +
                titleBounds.size.x / 2.f,
            titleBounds.position.y));

    titleText.setPosition(
        sf::Vector2f(450.f, 100.f));

    // FRAME BACKGROUND

    frameBackground.setSize(
        sf::Vector2f(520.f, 360.f));

    frameBackground.setFillColor(
        sf::Color(8, 15, 35));

    frameBackground.setPosition(
        sf::Vector2f(190.f, 250.f));

    // FRAME BORDER

    frameShape.setSize(
        sf::Vector2f(520.f, 360.f));

    frameShape.setFillColor(
        sf::Color::Transparent);

    frameShape.setOutlineColor(
        sf::Color::Cyan);

    frameShape.setOutlineThickness(4.f);

    frameShape.setPosition(
        sf::Vector2f(190.f, 250.f));

    // SHIP

    shipSprite = nullptr;

    if (!shipTextures.empty())
    {
        shipSprite =
            new sf::Sprite(*shipTextures[0]);

        sf::Vector2u size =
            shipTextures[0]->getSize();

        if (size.x > 0 && size.y > 0)
        {
            float scale =
                120.f /
                static_cast<float>(size.x);

            shipSprite->setScale(
                sf::Vector2f(scale, scale));
        }

        sf::FloatRect bounds =
            shipSprite->getLocalBounds();

        shipSprite->setOrigin(
            sf::Vector2f(
                bounds.position.x +
                    bounds.size.x / 2.f,
                bounds.position.y +
                    bounds.size.y / 2.f));

        // Tàu nằm bên trái
        shipSprite->setPosition(
            sf::Vector2f(315.f, 405.f));
    }

    // SHIP NAME

    shipNameText.setString("LION");
    shipNameText.setCharacterSize(20);
    shipNameText.setFillColor(
        sf::Color::Cyan);

    sf::FloatRect nameBounds =
        shipNameText.getLocalBounds();

    shipNameText.setOrigin(
        sf::Vector2f(
            nameBounds.position.x +
                nameBounds.size.x / 2.f,
            nameBounds.position.y));

    // TÊN ĐẶT TRÊN ĐẦU TÀU
    shipNameText.setPosition(
        sf::Vector2f(315.f, 315.f));

    // SHIP COUNT

    shipCountText.setString("1 / 3");
    shipCountText.setCharacterSize(25);
    shipCountText.setFillColor(
        sf::Color::Cyan);

    sf::FloatRect countBounds =
        shipCountText.getLocalBounds();

    shipCountText.setOrigin(
        sf::Vector2f(
            countBounds.position.x +
                countBounds.size.x / 2.f,
            countBounds.position.y));

    shipCountText.setPosition(
        sf::Vector2f(190.f, 535.f));

    // ATTRIBUTES

    attributesText.setString("ATTRIBUTES");
    attributesText.setCharacterSize(17);
    attributesText.setFillColor(
        sf::Color::Cyan);

    attributesText.setPosition(
        sf::Vector2f(480.f, 320.f));

    healthIcon.setString("HP");
    healthIcon.setCharacterSize(15);
    healthIcon.setFillColor(
        sf::Color::Red);

    healthIcon.setPosition(
        sf::Vector2f(470.f, 370.f));

    fireRateIcon.setString("FR");
    fireRateIcon.setCharacterSize(15);
    fireRateIcon.setFillColor(
        sf::Color::Yellow);

    fireRateIcon.setPosition(
        sf::Vector2f(470.f, 415.f));

    speedIcon.setString("SPD");
    speedIcon.setCharacterSize(15);
    speedIcon.setFillColor(
        sf::Color::White);

    speedIcon.setPosition(
        sf::Vector2f(470.f, 460.f));

    // INSTRUCTION

    instructionText.setString(
        "</>: SELECT     ENTER: START     ESC: BACK");

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

    // INITIAL SELECTION

    RefreshSelection();
}

// DESTRUCTOR

ShipSelectionMenu::~ShipSelectionMenu()
{
    delete shipSprite;
}

// DRAW STAT BAR

void ShipSelectionMenu::DrawStatBar(
    sf::RenderWindow &window,
    float x,
    float y,
    int currentLevel,
    int maxLevel)
{
    // 12 ô nhỏ
    const float segmentWidth = 10.f;
    const float segmentHeight = 12.f;
    const float gap = 2.f;

    for (int i = 0; i < maxLevel; i++)
    {
        sf::RectangleShape segment;

        segment.setSize(
            sf::Vector2f(
                segmentWidth,
                segmentHeight));

        segment.setPosition(
            sf::Vector2f(
                x + i * (segmentWidth + gap),
                y));

        if (i < currentLevel)
        {
            segment.setFillColor(
                sf::Color::Cyan);
        }
        else
        {
            segment.setFillColor(
                sf::Color(35, 45, 65));
        }

        segment.setOutlineColor( 
            sf::Color(70, 90, 110));

        segment.setOutlineThickness(
            1.f);

        window.draw(segment);
    }
}

// REFRESH SELECTION

void ShipSelectionMenu::RefreshSelection()
{
    if (shipSprite != nullptr)
    {
        delete shipSprite;
        shipSprite = nullptr;
    }

    if (shipTextures.empty())
        return;

    // CREATE SELECTED SHIP

    shipSprite =
        new sf::Sprite(
            *shipTextures[selectedShip]);

    sf::Vector2u size =
        shipTextures[selectedShip]->getSize();

    if (size.x > 0 && size.y > 0)
    {
        float scale =
            120.f /
            static_cast<float>(size.x);

        shipSprite->setScale(
            sf::Vector2f(scale, scale));
    }

    sf::FloatRect bounds =
        shipSprite->getLocalBounds();

    shipSprite->setOrigin(
        sf::Vector2f(
            bounds.position.x +
                bounds.size.x / 2.f,
            bounds.position.y +
                bounds.size.y / 2.f));

    // SHIP POSITION

    shipSprite->setPosition(
        sf::Vector2f(315.f, 405.f));

    // DEMO SHIP DATA

    if (selectedShip == 0)
    {
        shipName = "LION";

        healthLevel = 10;
        fireRateLevel = 10;
        speedLevel = 10;
    }
    else if (selectedShip == 1)
    {
        shipName = "DOFFIN";

        healthLevel = 10;
        fireRateLevel = 12;
        speedLevel = 8;
    }
    else
    {
        shipName = "BAT";

        healthLevel = 10;
        fireRateLevel = 8;
        speedLevel = 12;
    }

    // SHIP NAME

    shipNameText.setString(
        shipName);

    sf::FloatRect nameBounds =
        shipNameText.getLocalBounds();

    shipNameText.setOrigin(
        sf::Vector2f(
            nameBounds.position.x +
                nameBounds.size.x / 2.f,
            nameBounds.position.y));

    // Tên ở trên tàu
    shipNameText.setPosition(
        sf::Vector2f(315.f, 315.f));

    // SHIP COUNT

    shipCountText.setString(
        std::to_string(selectedShip + 1) +
        " / " +
        std::to_string(
            static_cast<int>(
                shipTextures.size())));

    sf::FloatRect countBounds =
        shipCountText.getLocalBounds();

    shipCountText.setOrigin(
        sf::Vector2f(
            countBounds.position.x +
                countBounds.size.x / 2.f,
            countBounds.position.y));

    shipCountText.setPosition(
        sf::Vector2f(315.f, 490.f));
}

// SET SELECTED SHIP

void ShipSelectionMenu::SetSelectedShip(
    int index)
{
    if (shipTextures.empty())
        return;

    int count =
        static_cast<int>(
            shipTextures.size());

    selectedShip =
        index % count;

    if (selectedShip < 0)
        selectedShip += count;

    RefreshSelection();
}

// MOVE SELECTION

void ShipSelectionMenu::MoveSelection(
    int delta)
{
    SetSelectedShip(
        selectedShip + delta);
}

// UPDATE

void ShipSelectionMenu::Update()
{
    // Input được xử lý trong Game.cpp.
}

// ANIMATION

void ShipSelectionMenu::UpdateAnimation(
    float deltaTime)
{
    // Chưa thêm animation.
}

// RENDER

void ShipSelectionMenu::Render(
    sf::RenderWindow &window)
{
    // Khung nền
    window.draw(frameBackground);

    // Viền
    window.draw(frameShape);

    // Title
    window.draw(titleText);

    // Attributes
    window.draw(attributesText);

    // Ship name
    window.draw(shipNameText);

    // Ship
    if (shipSprite != nullptr)
        window.draw(*shipSprite);

    // Icons
    window.draw(healthIcon);
    window.draw(fireRateIcon);
    window.draw(speedIcon);

    // Stat bars
    DrawStatBar(
        window,
        520.f,
        370.f,
        healthLevel);

    DrawStatBar(
        window,
        520.f,
        415.f,
        fireRateLevel);

    DrawStatBar(
        window,
        520.f,
        460.f,
        speedLevel);

    // Ship 1 / 3
    window.draw(shipCountText);

    // Instruction
    window.draw(instructionText);
}

// GET SELECTED SHIP

int ShipSelectionMenu::GetSelectedShip() const
{
    return selectedShip;
}
int ShipSelectionMenu::GetHealthLevel() const
{
    return healthLevel;
}

int ShipSelectionMenu::GetFireRateLevel() const
{
    return fireRateLevel;
}

int ShipSelectionMenu::GetSpeedLevel() const
{
    return speedLevel;
}