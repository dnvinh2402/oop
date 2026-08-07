#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::Font* font;
    sf::Sprite* bgSprite;
    
    // --- BIẾN ẢNH CHO LOGO (Thay thế cho titleText và introText) ---
    sf::Texture* logoTexture;
    sf::Sprite* logoSprite;

    // --- BIẾN ẢNH CHO NÚT BẤM (Thay cho chữ) ---
    sf::Texture* playTexture;
    sf::Sprite* playSprite;

    sf::Texture* historyTexture;
    sf::Sprite* historySprite;

    // Các biến âm thanh giữ nguyên
    sf::Texture* muteTexture;
    sf::Texture* unmuteTexture;
    sf::Texture* plusTexture;
    sf::Texture* minusTexture;

    sf::Sprite* muteButtonSprite;
    sf::Sprite* volumeUpSprite;
    sf::Sprite* volumeDownSprite;

    bool isMuted;
    int currentVolume;

public:
    MainMenu(sf::Font* f, sf::Texture* bgTexture, int highScore);
    ~MainMenu();

    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window);

    bool IsMuted() const;
    int GetVolume() const;
    void SetVolume(int vol, bool muted);
};