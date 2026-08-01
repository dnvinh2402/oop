#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::Font* font;
    sf::Sprite* bgSprite;
    
    sf::Text titleText;
    sf::Text introText;
    sf::Text playButton;
    sf::Text historyButton; // Dùng biến này thay cho highScoreText

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

    // Chỉ để lại khai báo, bỏ phần ngoặc nhọn {} đi
    bool IsMuted() const;
    int GetVolume() const;
    void SetVolume(int vol, bool muted);
};