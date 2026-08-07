#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Player.hpp"

class UI
{
private:
    sf::Font *font;
    sf::Text scoreText;
    sf::Texture heartTexture;
    int currentLives;

    sf::Text shieldText;
    sf::Texture shieldTexture;
    bool hasShield;

    float currentShieldTime;
    int currentShieldHits;

    float currentDoubleShotTime;
    sf::Text doubleShotText;
    sf::Texture doubleShotTexture;
    bool hasDoubleShot;

    sf::Text titleText;
    sf::Text subText;
    sf::Text scoreResultText;

    sf::RectangleShape overlay;
    GameState state;

public:
    UI(sf::Font *font);
    ~UI();

    void Update(Player *player, GameState currentState, int highScore);
    void Render(sf::RenderWindow &window);
};