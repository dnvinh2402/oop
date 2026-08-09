#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class PauseMenu {
private:
    sf::Font* font;
    
    // Phông nền làm mờ
    sf::RectangleShape backgroundOverlay;
    
    // Biến ảnh khung nền
    std::unique_ptr<sf::Texture> menuBgTexture;
    std::unique_ptr<sf::Sprite> menuBgSprite;

    // Các biến hình ảnh icon
    std::unique_ptr<sf::Texture> pauseTexture;
    std::unique_ptr<sf::Sprite> pauseSprite;

    std::unique_ptr<sf::Texture> resumeTexture;
    std::unique_ptr<sf::Sprite> resumeSprite;

    std::unique_ptr<sf::Texture> homeTexture;
    std::unique_ptr<sf::Sprite> homeSprite;

    std::unique_ptr<sf::Texture> unmuteTexture;
    std::unique_ptr<sf::Texture> muteTexture;
    std::unique_ptr<sf::Sprite> muteSprite;

    std::unique_ptr<sf::Texture> minusTexture;
    std::unique_ptr<sf::Sprite> minusSprite;

    std::unique_ptr<sf::Texture> plusTexture;
    std::unique_ptr<sf::Sprite> plusSprite;

    // Chỉ còn văn bản hiện % âm lượng
    sf::Text volumeText;

    float volume;
    bool isMuted;

public:
    PauseMenu(sf::Font* f);
    ~PauseMenu() = default;

    PauseMenu(const PauseMenu&) = delete;
    PauseMenu& operator=(const PauseMenu&) = delete;

    bool IsPauseButtonClicked(sf::Vector2f mousePos) const;
    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window, bool isPausedState);

    bool IsMuted() const;
    float GetVolume() const;
    void SetVolume(float vol, bool muted);
};