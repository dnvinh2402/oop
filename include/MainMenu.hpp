#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class MainMenu {
private:
    sf::Font* font;
    std::unique_ptr<sf::Sprite> bgSprite;
    
    // --- BIẾN ẢNH CHO LOGO (Thay thế cho titleText và introText) ---
    std::unique_ptr<sf::Texture> logoTexture;
    std::unique_ptr<sf::Sprite> logoSprite;

    // --- BIẾN ẢNH CHO NÚT BẤM (Thay cho chữ) ---
    std::unique_ptr<sf::Texture> playTexture;
    std::unique_ptr<sf::Sprite> playSprite;

    std::unique_ptr<sf::Texture> historyTexture;
    std::unique_ptr<sf::Sprite> historySprite;

    // Các biến âm thanh giữ nguyên
    std::unique_ptr<sf::Texture> muteTexture;
    std::unique_ptr<sf::Texture> unmuteTexture;
    std::unique_ptr<sf::Texture> plusTexture;
    std::unique_ptr<sf::Texture> minusTexture;

    std::unique_ptr<sf::Sprite> muteButtonSprite;
    std::unique_ptr<sf::Sprite> volumeUpSprite;
    std::unique_ptr<sf::Sprite> volumeDownSprite;

    bool isMuted;
    int currentVolume;

public:
    MainMenu(sf::Font* f, sf::Texture* bgTexture, int highScore);
    ~MainMenu() = default;

    MainMenu(const MainMenu&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;

    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window);

    bool IsMuted() const;
    int GetVolume() const;
    void SetVolume(int vol, bool muted);
};