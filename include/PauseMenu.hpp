#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu {
private:
    sf::Font* font;
    
    // Phông nền làm mờ
    sf::RectangleShape backgroundOverlay;
    
    // Biến ảnh khung nền
    sf::Texture* menuBgTexture;
    sf::Sprite* menuBgSprite;

    // Các biến hình ảnh icon
    sf::Texture* pauseTexture;
    sf::Sprite* pauseSprite;

    sf::Texture* resumeTexture;
    sf::Sprite* resumeSprite;

    sf::Texture* homeTexture;
    sf::Sprite* homeSprite;

    sf::Texture* unmuteTexture;
    sf::Texture* muteTexture;
    sf::Sprite* muteSprite;

    sf::Texture* minusTexture;
    sf::Sprite* minusSprite;

    sf::Texture* plusTexture;
    sf::Sprite* plusSprite;

    // Chỉ còn văn bản hiện % âm lượng
    sf::Text volumeText;

    float volume;
    bool isMuted;

public:
    PauseMenu(sf::Font* f);
    ~PauseMenu(); 

    bool IsPauseButtonClicked(sf::Vector2f mousePos) const;
    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window, bool isPausedState);

    bool IsMuted() const;
    float GetVolume() const;
    void SetVolume(float vol, bool muted);
};